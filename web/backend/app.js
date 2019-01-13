const cfg        = require('./cfg')
const express    = require('express')
const cors       = require('cors')
const bodyParser = require('body-parser')
const Store      = require('./store')
const Comm       = require('./comm')
const Mailer     = require('./mailer')
const Sheets     = require('./sheets')
const validator  = require('validator')

class Controller
{
  constructor(cfg)
  {
    this.express_ = express()
    this.store_   = new Store();
    this.comm_    = new Comm()
    this.mailer_  = new Mailer(cfg.mailer)
    this.sheets_  = new Sheets(cfg.sheets)

    this.init_()
  }

  initExpress_()
  {
    
  }

  init_()
  {
    // hookup express
    ///////////////////////////////////////////////////////////////////////////
    this.express_.use(cors())
    this.express_.use(bodyParser.json())
    this.express_.use(bodyParser.urlencoded({ extended: true }))

    this.express_.use(async (err, req, res, next) =>
    {
      console.error(req.body)
      next()
    })

    this.express_.get('/api/v1/devices', async (req, res, next) =>
    {
      try
      {
        res.json(await this.store_.getDevices())
      }
      catch(err) { next(err) } 
    })

    this.express_.patch('/api/v1/devices', async (req, res, next) =>
    {
      try
      {
        const device = await this.store_.getDevice(req.body.id)

        if('sheetsEmail' in req.body &&
           device.sheetsEmail != req.body.sheetsEmail)
        {
          device.sheetsEmail = req.body.sheetsEmail
          
          if(device.sheetsEmail)
          {
            device.sheetsId = await this.sheets_.createSheet(
            { 
              title:     `boopr device ${device.name || device.id} log`,
              shareWith: device.sheetsEmail
            })
          }
          else
          {
            device.sheetsId = ''
          }
        }

        if('email' in req.body && 
           device.email != req.body.email)
        {
          device.email = req.body.email
        }

        if('name' in req.body && 
           device.name != req.body.name)
        {
          device.name = req.body.name
        }
        
        if('script' in req.body)
        {
          device.script = req.body.script

          await this.comm_.setNodeScript(device.id, 0, device.script)
        }

        res.json(await this.store_.updateDevice(device.id, device))
      }
      catch(err) { next(err) } 
    })
	
    this.express_.delete('/api/v1/devices', async (req, res, next) =>
    {
      try
      {
        await this.store_.deleteDevice(req.body.id)
        res.send({})
      }
      catch(err) { next(err) } 
    })

    this.express_.use(async (err, req, res, next) =>
    {
      console.error(err)
      res.status(err.status || 500).json({ message: err.message })
    })

    this.express_.listen(9090, () =>
    {
      console.log(`ok`)
    })

    // hookup comm
    ///////////////////////////////////////////////////////////////////////////
    this.comm_.addTCPServerTransport('tcp-server', '0.0.0.0', 8081)

    this.comm_.on('open', () =>
    {
    })

    this.comm_.on('msg', async msg =>
    {
      try
      {
        let device         = await this.store_.getDevice(msg.deviceId)
        if(!device) device = await this.store_.newDevice(msg.deviceId)

        if(device.email)
        {
          await this.mailer_.send(
            device.email, 
            `device ${device.name || device.id} update`, 
            `${device.data}`)
        }

        if(device.sheetsId)
        {
          await this.sheets_.appendData(
            device.sheetsId, 
            [
              '=NOW()',
              msg.functionCode,
              msg.data.join()
            ])
        }
      }
      catch(err) { console.error(err) }
    })

    this.comm_.on('error', err =>
    {
      if(err) console.error(err)
    })
  }

  handle_msg()
  {
    
  }
};

const controller = new Controller(cfg)
