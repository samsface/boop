const nodemailer = require('nodemailer');

class Mailer
{
    constructor(cfg)
    {
      this.events = 
      {
      }

      this.transport_ = nodemailer.createTransport(
      {
        service: 'gmail',
        auth: 
        {
          user: cfg.user,
          pass: cfg.pass
        }
      })
    }

    send(to, subject, text)
    {
      return new Promise((resolve, reject) =>
      {
        const args =
        {
          from: '"boopr bot 🤖" <boopr.bot@gmail.com>',
          to,
          subject,
          text
        }
      
        this.transport_.sendMail(args, err =>
        {
          if(err) reject(err)
          else    resolve()
        })
      })
    }

    on(name, fnc) { this.events_[name] = fnc }
}

module.exports = Mailer
