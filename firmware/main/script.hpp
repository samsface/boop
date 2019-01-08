#pragma once

#include "array.hpp"
#include "ring.hpp"
#include "optional.hpp"
#include "message.hpp"
#include "components.hpp"

// ui32/ui8/ui32 ui8[]

// set 65536/button/255 green\n
// set 65536/oled/255 "1/4"\n
// set 65536/speaker/255 success\n

// set 65536/button_primary_led set_led0_solid_green,wait_for_button0_read,set_led0_solid_off
// set 65536/button_primary_led (green,wait_for_read,none)
// set 65536/button_primary_led (wait_for_push,goto_start)
// set 65536/set_script0 led0_off,wait_for_button0_read,led0_flash_orange,wait_for_ack_for_5s,led0_solid_green,wait_for_1s,goto_start

// set 65536/set_script0 led0_off,wait_for_button0_read,led0_flash_orange,wait_for_ack_for_5s,led0_solid_green,wait_for_1s,goto_start

// set 65536/nfc (wait_for_read,none)

// set 65536

// evt 255/button/255 down

namespace script
{  
const byte set_led0_off = 1;

const byte set_led0_solid_white   = 2;
const byte set_led0_solid_red     = 3;
const byte set_led0_solid_orange  = 4;
const byte set_led0_solid_yellow  = 5;
const byte set_led0_solid_green   = 6;
const byte set_led0_solid_blue    = 7;
const byte set_led0_solid_purple  = 8;

const byte set_led0_flash_white   = 9;
const byte set_led0_flash_red     = 10;
const byte set_led0_flash_orange  = 11;
const byte set_led0_flash_yellow  = 12;
const byte set_led0_flash_green   = 13;
const byte set_led0_flash_blue    = 14;
const byte set_led0_flash_purple  = 15;

const byte set_led1_off = 16;

const byte set_led1_solid_white   = 17;
const byte set_led1_solid_red     = 18;
const byte set_led1_solid_orange  = 19;
const byte set_led1_solid_yellow  = 20;
const byte set_led1_solid_green   = 21;
const byte set_led1_solid_blue    = 22;
const byte set_led1_solid_purple  = 23;

const byte set_led1_flash_white   = 24;
const byte set_led1_flash_red     = 25;
const byte set_led1_flash_orange  = 26;
const byte set_led1_flash_yellow  = 27;
const byte set_led1_flash_green   = 28;
const byte set_led1_flash_blue    = 29;
const byte set_led1_flash_purple  = 30;

const byte make_noise_success = 31;
const byte make_noise_info    = 32;
const byte make_noise_warning = 33;
const byte make_noise_danger  = 34;

const byte wait_for_button0_down = 35;
const byte wait_for_button1_down = 36;

const byte wait_for_ack_with_1s_timeout = 37;
const byte wait_for_ack_with_5s_timeout = 38;

const byte wait_for_500ms = 39;
const byte wait_for_1s    = 40;

const byte goto_start = 100;

struct reading
{
  unsigned short ack = 0;
  byte instruction = 0;
  array<byte, 16> value;

  reading() = default;

  reading(unsigned short ack, byte instruction, byte byte_value) :
  ack{ ack },
  instruction{ instruction }
  {
    value.push_back(byte_value);
  }
};

class script
{
  array<byte, 16> instructions;
  byte instruction_pointer = 0;
  unsigned long wait_ = 0;
  optional<reading> last_reading_;

  void set_led_color(components::led_rgb& led, byte r, byte g, byte b)
  {
    led.set_color(r, g, b);
    instruction_pointer++;
  }

  optional<reading> wait_for_button_down(byte instruction, components::button& button)
  {    
    auto button_reading = button.read();
    if(button_reading && button_reading.value() == HIGH)
    {
      instruction_pointer++;
      return last_reading_ = { static_cast<unsigned short>(random(1, 65536)), instruction, button_reading.value() };
    }
    else return last_reading_ = {};
  }

  void wait_for_time(unsigned long wait_time)
  {
    if(wait_ == 0)
    {
      wait_ = millis();
    }
    else if(millis() - wait_ > wait_time)
    {
      wait_ = 0;
      instruction_pointer++;
    }
  }

  optional<reading> wait_for_ack(unsigned long wait_time)
  {
    if(!last_reading_)
    {
      wait_ = 0;
      last_reading_ = {};
      instruction_pointer++;
    }
    else if(wait_ == 0)
    {
      wait_ = millis();
    }
    else if(millis() - wait_ > wait_time)
    {
      reset();
    }
   
    return {};
  }

  void reset()
  {
    wait_ = 0;
    last_reading_ = {};
    instruction_pointer = 0;
  }

public:

  script() = default;

  script(array<byte, 16> instructions) : instructions{ instructions }
  {}

  optional<reading> tick(components::module& module)
  {    
    optional<reading> reading;
    
    if(instruction_pointer < instructions.size())
    {
      byte i = instructions[instruction_pointer];

           if(i == set_led0_off)          set_led_color(module.led0, 0, 0, 0);
      else if(i == set_led0_solid_white)  set_led_color(module.led0, 255, 255, 255);
      else if(i == set_led0_solid_red)    set_led_color(module.led0, 255, 0,   0);
      else if(i == set_led0_solid_orange) set_led_color(module.led0, 255, 128, 0);
      else if(i == set_led0_solid_yellow) set_led_color(module.led0, 255, 255, 0);
      else if(i == set_led0_solid_green)  set_led_color(module.led0, 0,   255, 0);
      else if(i == set_led0_solid_blue)   set_led_color(module.led0, 0,   0,   255);
      else if(i == set_led0_solid_purple) set_led_color(module.led0, 127, 0,   255);

      else if(i == set_led1_off)          set_led_color(module.led1, 0, 0, 0);
      else if(i == set_led1_solid_white)  set_led_color(module.led1, 255, 255, 255);
      else if(i == set_led1_solid_red)    set_led_color(module.led1, 255, 0,   0);
      else if(i == set_led1_solid_orange) set_led_color(module.led1, 255, 128, 0);
      else if(i == set_led1_solid_yellow) set_led_color(module.led1, 255, 255, 0);
      else if(i == set_led1_solid_green)  set_led_color(module.led1, 0,   255, 0);
      else if(i == set_led1_solid_blue)   set_led_color(module.led1, 0,   0,   255);
      else if(i == set_led1_solid_purple) set_led_color(module.led1, 127, 0,   255);
           
      else if(i == wait_for_button0_down) reading = wait_for_button_down(wait_for_button0_down, module.button0);
      else if(i == wait_for_button1_down) reading = wait_for_button_down(wait_for_button1_down, module.button1);
      
      else if(i == wait_for_500ms) wait_for_time(100);
      else if(i == wait_for_1s)    wait_for_time(1000);

      else if(i == wait_for_ack_with_1s_timeout) reading = wait_for_ack(1000);
      else if(i == wait_for_ack_with_5s_timeout) reading = wait_for_ack(5000);

      else if(goto_start) reset();
    }

    return reading;
  }

  void clear_ack(unsigned short ack_to_clear)
  {
    if(last_reading_ && last_reading_->ack == ack_to_clear) last_reading_ = {};
  }
};

class runner
{
  ring<script, 1> scripts_;
  components::module module_;

public:

  optional<reading> tick()
  {     
    return scripts_.next().tick(module_);
  }

  void set(size_t i, array<byte, 16> instructions)
  { 
    if(i < 4)
    {
      scripts_[i] = { instructions };
    }
  }

  void clear_ack(unsigned short ack_to_clear)
  {
    for(auto i = 0; i < scripts_.size(); i++)
    {
      scripts_[i].clear_ack(ack_to_clear);
    }
  }
};
}
