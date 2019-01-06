#include "config.hpp"
#include "comm.hpp"
#include "script.hpp"

void(*g_reboot)(void) = 0;

struct comms
{
  const config::config& c;
  comm::client<comm::channel::hardware_serial, comm::protocol> serial;
  comm::client<comm::channel::wifi, comm::protocol> wifi;

  comms(const config::config& c) : c{ c }
  {}

  void write(const message& m)
  {
    serial.write(m);
    wifi.write(m);
  }

  template<typename ...Args>
  void write_event(Args ...args)
  {
    serial.write_event(args...);
    wifi.write_event(args...);
  }

  template<typename ...Args>
  void write_ack(Args ...args)
  {
    serial.write_ack(args...);
    wifi.write_ack(args...);
  }
};

class controller
{
  config::config config_;
  comms comm_; 
  script::runner script_runner_;
 
  void handle_ack(const message& msg)
  {
    if(msg.address == config_.address.get())
    {
      script_runner_.clear_ack(msg.ack);
    }

    if(config_.is_relay.get())
    {
      comm_.write(msg);
    }
  }

  void handle_function(const message& msg)
  {  
    if(msg.address == config_.address.get())
    {
           if(msg.function_code == reboot)        g_reboot();
      else if(msg.function_code == set_script0)   script_runner_.set(0, msg.value);
      else if(msg.function_code == set_script1)   script_runner_.set(1, msg.value);
      else if(msg.function_code == set_script2)   script_runner_.set(2, msg.value);
      else if(msg.function_code == set_script3)   script_runner_.set(3, msg.value);
      else if(msg.function_code == set_address)   config_.address.set(msg.value[1]);
      else if(msg.function_code == set_is_relay)  config_.is_relay.set(msg.value[0]);
      else if(msg.function_code == set_wifi_ssid) config_.wifi_ssid.set(msg.value);
      else if(msg.function_code == set_wifi_pass) config_.wifi_pass.set(msg.value);

      comm_.write_ack(msg.address, msg.ack);
    }
    else if(config_.is_relay.get())
    {
      comm_.write(msg);
    }
  }

  void handle_event(const message& msg)
  {
    if(config_.is_relay.get())
    {
      comm_.write(msg);
    }
  }

  void handle_message(const optional<message>& optional_msg)
  {    
    if(optional_msg)
    {
      const auto& msg = optional_msg.value();

           if(msg.is_ack())      handle_ack(msg);
      else if(msg.is_function()) handle_function(msg);
      else if(msg.is_event())    handle_event(msg);
    }
  }
    
  void read_comms()
  {
    handle_message(comm_.serial.read());
    handle_message(comm_.wifi.read());
  }
    
  void check_health()
  {
    comm_.wifi.check_health();
  }

  void run_scripts()
  {
    auto reading = script_runner_.tick();

    if(reading)
    {
      comm_.write_event(
        config_.address.get(), 
        reading->ack, 
        reading->instruction,
        reading->value);
    }
  }
    
public:

  controller() : comm_{ config_ }
  {}

  void tick()
  {
      read_comms();
      
      check_health();
      
      run_scripts();
  }
    
  void tick(size_t count)
  {
      while(--count + 1 != 0) tick();
  }
};
