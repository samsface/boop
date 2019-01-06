#pragma once

namespace components
{
// led 
///////////////////////////////////////////////////

class led
{
  byte pin_ = 200;
  byte value_ = 0;

public:

  led() = default;

  led(byte pin) : pin_{ pin }
  {
    //pinMode(pin_, OUTPUT);
  }

  void set_value(byte value)
  {
    value_ = value;
    analogWrite(pin_, value_);
  }
};

// led_rgb
///////////////////////////////////////////////////

class led_rgb
{
  led red_, green_, blue_;

public:

  led_rgb() = default;

  led_rgb(led red, led green, led blue) :
  red_{ red }, green_{ green }, blue_{ blue }
  {}

  void set_color(byte r, byte g, byte b)
  {
    red_.set_value(r);
    green_.set_value(g);
    blue_.set_value(b);
  }
};

// button
///////////////////////////////////////////////////

class button
{
  byte pin_ = 0;
  byte transient_value_ = 0;
  byte debounced_value_ = 0;

  unsigned long last_debounce_time_ = 0;
  unsigned long debounce_threshold_time_ = 25;

public:

  button() = default;

  button(byte pin) : pin_{ pin }
  {
    //pinMode(pin, INPUT_PULLUP);  
  }

  optional<byte> read()
  {
    auto new_value = 1 - digitalRead(pin_);

    if(new_value != transient_value_)
    {
      last_debounce_time_ = millis();
    }

    transient_value_ = new_value;

    if((millis() - last_debounce_time_) > debounce_threshold_time_)
    {
      if(transient_value_ != debounced_value_)
      {
        debounced_value_ = transient_value_;
        return optional<byte>{ debounced_value_ };
      }
    }

    return optional<byte>{};
  }
};

struct module
{
  led_rgb led0;
  led_rgb led1;
  button button0;
  button button1;

  module() : 
  led0{ 1, 200, 200 },
  led1{ 3, 200, 200 },
  button0{ 4 }
  {}
}; 
}
