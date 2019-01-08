const fs = require('fs');
const cfg = require('./cfg')
const readline = require('readline');
const {google} = require('googleapis');

class Sheets
{
  constructor(cfg)
  {
    this.cfg_ = cfg
    this.authorize_()
  }

  authorize_()
  {
    const { client_secret, client_id, redirect_uris, token } = this.cfg_.credentials

    const auth = new google.auth.OAuth2(client_id, client_secret, redirect_uris[0])
  
    this.ensureToken_(auth, (err, token) => 
    {
      if(err) console.error(err)
      else
      {
        cfg.token = token
        auth.setCredentials(token)
        this.sheets_ = google.sheets({ version: 'v4', auth })
        this.drive_  = google.drive( { version: 'v3', auth })
      }
    })
  }

  ensureToken_(auth, fnc)
  {
    if(this.cfg_.credentials.token) return fnc(null, this.cfg_.credentials.token)

    const authUrl = auth.generateAuthUrl(
    {
      access_type: 'offline',
      scope:       ['https://www.googleapis.com/auth/spreadsheets', 'https://www.googleapis.com/auth/drive']
    })

    console.log('Authorize this app by visiting this url:', authUrl)

    const rl = readline.createInterface(
    {
      input:  process.stdin,
      output: process.stdout,
    })

    rl.question('Enter the code from that page here: ', code => 
    {
      rl.close()

      auth.getToken(code, fnc)
    })
  }

  sharePage_(args, fnc)
  {
    const permissions = 
    {
      'type': 'user',
      'role': 'writer',
      'emailAddress': 'samsface@gmail.com'
    }
    
    this.drive_.permissions.create(
    {
      resource: permissions,
      fileId:   args.fileId,
      fields:   'id',
    }, 
    fnc)
  }

  createSheet(args)
  {
    console.log(args)
    return new Promise((resolve, reject) =>
    {
      this.sheets_.spreadsheets.create(
      { 
        resource:
        {
          properties: 
          {
            title: args.title
          }
        },
        fields: 'spreadsheetId',
      }, 
      (err, sheet) => 
      {
        if(err) reject(err)
        else    
        {
          setTimeout(() => 
          {
            this.sharePage_({ fileId: sheet.data.spreadsheetId, shareWidth: args.shareWith }, err =>
            {
              if(err) reject(err)
              else    resolve(sheet.data.spreadsheetId)
            })
          }, 
          1000)
        }
      })
    })
  }

  appendData(spreadsheetId, values)
  {
    return new Promise((resolve, reject) =>
    {  
      this.sheets_.spreadsheets.values.append(
      {
        spreadsheetId,
        range: 'Sheet1',
        valueInputOption: 'USER_ENTERED',
        insertDataOption: 'INSERT_ROWS',
        resource:
        {
          values: [values]
        }
      }, 
      (err, res) => 
      {
        if(err) reject(err)
        else    resolve(res)
      })
    })
  }
}

module.exports = Sheets
