const Comm = require('./comm')

const comm = new Comm();

let i = 0;

comm.on('msg', msg =>
{
  console.log(msg, i++)
})

comm.on('error', (err, channel) =>
{
  console.log(err)
})

//comm.set_script0(123, [ ic.set_led0_off, ic.wait_for_button0_down, ic.set_led0_solid_white, ic.wait_for_500ms, ic.goto_start ])

let stuff = {}


const program = require('commander')

function success(msg)
{
  console.log(msg)
  process.exit(0)
}

function error(err)
{
  console.error(err)
  process.exit(1)
}

function resolveTransport(cmd, comm)
{
  if(cmd.parent.tcpServerPort)
  {
    console.log(`Adding tcp server transport ${cmd.parent.tcpServerPort}...`)
    comm.addTCPServerTransport('tcp', '0.0.0.0', cmd.parent.tcpServerPort)
  }
  else
  {
    console.log(`Adding serial port transport ${cmd.parent.serialPort}...`)
    comm.addSerialTransport('serial', cmd.parent.serialPort)
  }
}

program
  .option('--serial-port <port>', 'serial port to use', '/dev/ttyUSB0')
  .option('--tcp-server-port <port>', 'tcp server port to use')

program
  .command('set-node-is-relay <node> <is-relay>')
  .description('sets node to relay all comm it receives')
  .action((node, isRelay, cmd) =>
  {
    isRelay = JSON.parse(isRelay) ? true : false

    resolveTransport(cmd, comm)
   
    comm.on('error', err => error(err))

    comm.on('open', err =>
    {
      if(err) error(err)
      else
      {
        console.log(`Setting node=${node} to relay=${isRelay}...`)
        comm.setNodeAsRelay(node, JSON.parse(isRelay), err =>
        {
          if(err) error(err)
          else    success('Success!')
        })
      }
    })
  })

program
  .command('set-node-address <node> <address>')
  .description('sets address of given node')
  .action((node, address, cmd) =>
  {
    resolveTransport(cmd, comm)

    comm.on('error', err => error(err))

    comm.on('open', err =>
    {
      if(err) error(err)
      else
      {
        console.log(`Setting node=${node} to address=${address}...`)
        comm.setNodeAddress(node, address, err =>
        {
          if(err) error(err)
          else    success('Success!')
        })
      }
    })
  })

program
  .command('set-node-script <node> <script-idx> [script...]')
  .description(`sets a script at a given idx for a given node`)
  .action((node, scriptIdx, script, cmd) =>
  {
    resolveTransport(cmd, comm)

    comm.on('error', err => error(err))

    comm.on('open', err =>
    {
      if(err) error(err)
      else
      {
        console.log(`Setting node=${node} script=${scriptIdx}...`)
        comm.setNodeScript(node, scriptIdx, script, err =>
        {
          if(err) error(err)
          else    success('Success!')
        })
      }
    })
  })

program
  .command('monitor')
  .description(`monitor all comms between nodes`)
  .action(cmd =>
  {
    stuff.monitor    = true
    stuff.serialPort = cmd.parent.serialPort

    resolveTransport(cmd, comm)

    comm.on('msg', msg =>
    {
      console.log(msg)
      comm.ack(msg.address, msg.ackCode)
    })
  })
 
program.parse(process.argv)
