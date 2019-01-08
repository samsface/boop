import uuid from 'uuid/v4'

function get_option(name, url) 
{
   if (!url) url = window.location.href;
   name = name.replace(/[\[\]]/g, "\\$&");
   var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
       results = regex.exec(url);
   if (!results) return null;
   if (!results[2]) return '';
   return decodeURIComponent(results[2].replace(/\+/g, " "));
}

let _cfg = 
{
   session_id:    get_option('session_id')    || localStorage['session_id'],
   user_id:       get_option('user_id')       || localStorage['user_id'],
   has_seen_hero: get_option('has_seen_hero') || localStorage['has_seen_hero'] || false,
}

let cfg = { }

Object.keys(_cfg).forEach(key =>
{
   Object.defineProperty(cfg, key, 
   {
      set: val => this['_' + key] = (val ? localStorage[key] = val : val),
      get: ()  => this['_' + key]
   })

   cfg[key] = _cfg[key]
})

export default cfg
