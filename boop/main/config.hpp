#pragma once

#include <EEPROM.h>
#include "array.hpp"

namespace config
{
using buff16 = array<byte, 16>;

template<typename T, size_t Idx>
class setting
{
  T t_;

public:

  setting()
  {
    EEPROM.get(Idx, t_);
  }

  const T& get() const
  {
    return t_;
  }

  void set(const T& t)
  {
    t_ = t;
    EEPROM.put(Idx, t_);
  } 
};

struct config
{
  setting<unsigned int, 0> just_born;
  
  // node settings
  setting<unsigned short, 8> address;
  setting<bool, 16> is_relay;

  // wifi settings
  setting<buff16, 17> wifi_ssid;
  setting<buff16, 33> wifi_pass;

  // server settings
  setting<buff16, 49> server_hostname;
  setting<unsigned short, 65> server_port;
  
  config()
  {        
    if(just_born.get() != 27)
    { 
      for(int i = 0 ; i < EEPROM.length() ; i++) 
      {
        EEPROM.write(i, 0);
      }

      address.set(0);
      is_relay.set(false);

      just_born.set(27);
    }
  }
};
}
