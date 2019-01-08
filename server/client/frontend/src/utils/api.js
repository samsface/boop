import request from 'superagent'
import cfg     from '@/utils/cfg'

function get_devices(args, fnc)
{
  request
  .get(`${cfg.rest_endpoint}/devices`)
  .end((err, res) =>
  {
      if(err) fnc(err)
      else    fnc(null, JSON.parse(res.text))
  })
}

function set_device(args, fnc)
{
  request
  .patch(`${cfg.rest_endpoint}/devices`)
  .send(args)
  .end((err, res) =>
  {
      if(err) fnc(err)
      else    fnc(null, JSON.parse(res.text))
  })
}

export default 
{
  get_devices,
  set_device
}