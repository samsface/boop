#pragma once

#include "vector.hpp"
#include "optional.hpp"
#include "message.hpp"
#include "comm_channel.hpp"
#include "comm_protocol.hpp"

namespace comm
{
template <typename Channel, typename Protocol>
class client
{
  Channel channel_;
  Protocol protocol_;

public:

  optional<message> read()
  {
    if(channel_.available() > 0) 
    {           
      return protocol_(channel_.read());
    }
    else return {};
  }

  void write(const message& m)
  {
    auto buffer = protocol_(m);
    channel_.write(&buffer[0], buffer.size());
  }

  void write_event(unsigned short address, unsigned short ack_code, byte function_code, array<byte, 16> value)
  {
    write({ address, ack_code, function_code, value });
  }

  void write_ack(unsigned short address, unsigned short ack_code)
  {
    write({ address, ack_code, acking });
  }
    
  void keep_alive()
  {
    channel_.keep_alive();
  }
};
}
