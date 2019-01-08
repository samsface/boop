#pragma once

#include "array.hpp"
#include "optional.hpp"
#include "message.hpp"

namespace comm
{
class protocol
{
  array<byte, 23> buffer_;
  unsigned long last_read_time_ = 0;

  void check_if_timed_out()
  {
    if(millis() - last_read_time_ > 1000)
    {
      buffer_.clear();
    }
    
    last_read_time_ = millis();
  }

public:
    
  optional<message> operator()(byte b)
  {    
    check_if_timed_out();
    
    buffer_.push_back(b);
    
    if(buffer_.size() == 23)
    {
      message msg;
      msg.address       = buffer_[1] << 8;
      msg.address      += buffer_[0];
      msg.ack           = buffer_[3] << 8;
      msg.ack          += buffer_[2];
      msg.function_code = buffer_[4];
      
      for(int i = 7; i < buffer_.size(); i++)
      {
        msg.value.push_back(buffer_[i]);
      }

      buffer_.clear();
      
      return optional<message>{ msg };
    }
    else
    {
      return {};
    }
  }

  array<byte, 23> operator()(const message& msg) const
  {
    array<byte, 23> res;
    res.reserve(23);
    
    res[1] = msg.address >> 8;
    res[0] = msg.address;
    res[3] = msg.ack >> 8;
    res[2] = msg.ack;
    res[4] = msg.function_code;
    res[6] = msg.checksum;
    res[5] = msg.checksum >> 8;
    
    for(auto i = 7; i < 23; i++)
    {
      res[i] = msg.value[i - 7];
    }

    return res;
  }
};
}
