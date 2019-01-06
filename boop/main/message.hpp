#pragma once

const byte reboot        = 0;

const byte acking        = 1;

const byte set_script0   = 2;
const byte set_script1   = 3;
const byte set_script2   = 4;
const byte set_script3   = 5;

const byte set_address  = 6;
const byte set_is_relay = 7;

const byte set_wifi_ssid = 8;
const byte set_wifi_pass = 9;

struct message
{
  unsigned short address = 0;
  unsigned short ack = 0;
  byte function_code = 0;
  unsigned short checksum = 0;
  array<byte, 16> value;

  message() = default;

  message(unsigned short address, unsigned short ack, byte function_code) :
  address{ address }, ack{ ack }, function_code{ function_code }
  {}

  message(unsigned short address, unsigned short ack, byte function_code, array<byte, 16> value) :
  address{ address }, ack{ ack }, function_code{ function_code }, value{ value }
  {}

  message(unsigned short address, unsigned short ack, byte function_code, byte byte_value) :
  address{ address }, ack{ ack }, function_code{ function_code }
  {
    value.push_back(byte_value);
  }

  bool is_ack() const
  {
    return function_code == acking;
  }

  bool is_function() const
  {
    return (function_code > acking) && (function_code < 10);
  }

  bool is_event() const
  {
    return function_code > set_script3;
  }
};


