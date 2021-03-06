const sqlite3 = require('sqlite3').verbose();


class Store
{
  constructor()
  {
    this.db_ = new sqlite3.Database('test.db')

    this.db_.serialize(() =>
    {
      this.db_.run(`
      CREATE TABLE IF NOT EXISTS devices
      (
        id          INTEGER NOT NULL PRIMARY KEY, 
        name        TEXT    NOT NULL DEFAULT '', 
        type        TEXT    NOT NULL DEFAULT 'unknown',
        script      JSON    NOT NULL DEFAULT '[100, 100, 100, 100, 100, 100, 100, 100]',
        email       TEXT    NOT NULL DEFAULT '',
        sheetsEmail TEXT    NOT NULL DEFAULT '',
        sheetsId    TEXT    NOT NULL DEFAULT ''
      )`,
      (err) =>
      {
        if(err) console.error(err)
      })
    })
  }

  getDevices(args)
  {
    return new Promise((resolve, reject) =>
    {
      this.db_.all(`
      SELECT * FROM devices`, [], (err, res) =>
      {
        if(err) reject(err)
        else
        {
          for(const i in res) res[i].script = JSON.parse(res[i].script)
          resolve(res)
        }
      })
    })
  }

  getDevice(id)
  {
    return new Promise((resolve, reject) =>
    {
      this.db_.all(`SELECT * FROM devices WHERE id=?`, [id], (err, res) =>
      {
        if(err) reject(err)
        else
        {
          for(const i in res) res[i].script = JSON.parse(res[i].script)
          resolve(res && res.length !== 0 ? res[0] : null)
        }
      })
    })
  }

  newDevice(id, args)
  {    
    return new Promise((resolve, reject) =>
    {
      this.db_.run(`
      INSERT INTO devices(id) VALUES(?)`, 
      [id], 
      (err) =>
      {
        if(err) reject(err)
        else    resolve({ id })
      })
    })
  }

  updateDevice(id, args)
  {
    console.log('sam', args)
    return new Promise((resolve, reject) =>
    {
      this.db_.run(`
      UPDATE devices SET
        name        = IFNULL(?, name),
        script      = IFNULL(?, script),
        email       = IFNULL(?, email),
        sheetsEmail = IFNULL(?, sheetsEmail),
        sheetsId    = IFNULL(?, sheetsId)
      WHERE 
        id = ?`, 
      [args.name, JSON.stringify(args.script), args.email, args.sheetsEmail, args.sheetsId, id], 
      (err, res) =>
      {
        if(err) reject(err)
        else    resolve(args)
      })
    })
  }
  
  deleteDevice(id)
  {
    return new Promise((resolve, reject) =>
    {
      this.db_.run(`DELETE FROM devices WHERE id = ?`, 
      [id], 
      (err, res) =>
      {
		  console.log(err, res)
        if(err) reject(err)
        else    resolve()
      })
    })
  }
}

module.exports = Store
