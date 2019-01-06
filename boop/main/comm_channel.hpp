#pragma once

#include <SoftwareSerial.h>
//#include <Ethernet.h>
#include <ESP8266WiFi.h>

namespace comm
{
namespace channel
{
// hardware serial
/////////////////////////////////////////////////////

class hardware_serial
{
public:

  hardware_serial()
  {
    //Serial.begin(9600);
  }

  bool available() const
  { 
    return Serial.available(); 
  }

  void write(const byte* buf, size_t len)
  { 
    Serial.write(buf, len); 
  }

  byte read()
  { 
    return Serial.read();
  } 

  long strength() const
  {
    return 0;
  }
};

// software serial
/////////////////////////////////////////////////////

class software_serial
{
  SoftwareSerial serial_;

public:

  software_serial() : serial_{ 10, 11 }
  {
    serial_.begin(9600);
  }

  bool available()
  { 
    return serial_.available(); 
  }

  void write(const byte* buf, size_t len) 
  { 
    serial_.write(buf, len); 
  }

  byte read() 
  { 
    return serial_.read(); 
  }

  long strength() const
  {
    return 0;
  }
};

// rs485
/////////////////////////////////////////////////////

class rs485
{
  SoftwareSerial serial_;

public:

  rs485() : serial_{ 2, 3 }
  {
    serial_.begin(9600);
    pinMode(4, OUTPUT);
  }

  bool available()
  { 
    return serial_.available(); 
  }

  void write(const byte* buf, size_t len) 
  { 
    digitalWrite(4, HIGH);
    serial_.write(buf, len); 
    digitalWrite(4, LOW);
  }

  byte read() 
  { 
    return serial_.read(); 
  }

  long strength() const
  {
    return 0;
  }
};

// ethernet
/////////////////////////////////////////////////////
/*
class ethernet
{
  EthernetClient client_;

  connect()
  {
    if(!client_.connected())
    {
      client_.connect("", 80);
    }
  }
   
public:

  ethernet()
  {
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
    Ethernet.begin(mac);

    connect();
  }

  bool available() const
  { 
    return client_.available(); 
  }

  void write(const byte* buf, size_t len)
  { 
    client_.write(buf, len); 
  }

  byte read() 
  { 
    return client_.read(); 
  }

  long strength() const
  {
    return 0;
  }

  ~ethernet()
  {
    client_.stop();
  }
};
*/
// wifi
///////////////////////////////////////////////////////////////////////////////
/*
TX from ESP8266 is connected to D2, RX to D3 of the Arduino (via 1K resistor). 
Beware that the 3.3V from the Arduino is usually not sufficient* to power the 
ESP8266 module. The ESP8266 needs a separate 3.3V power source, eg. from a 
breadboard power connector:
*/

class wifi
{
  WiFiClient client_;

public:

  bool available()
  { 
    return client_.available();
  }

  void write(const byte* buf, size_t len)
  { 
    client_.write(buf, len); 
  }

  byte read() 
  { 
    return client_.read(); 
  }

  long strength() const
  {
    return WiFi.RSSI();
  }
    
  void check_health()
  {
    if(WiFi.status() == WL_IDLE_STATUS)
    {
        return;
    }
    else if(WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin("VM1EC2332", "j7a6Ntfzkrpr");
    }
    else if(client_.connected())
    {
        return;
    }
    else if(client_.connect("192.168.0.185", 8080))
    {
        return;
    }
  }

  ~wifi()
  {
    client_.stop();
  }
};

} // channel
} // comm
