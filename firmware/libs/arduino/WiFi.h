#pragma once

#include <Arduino.h>

const int WL_CONNECT_FAILED = 0;
const int WL_CONNECTION_LOST = 1;
const int WL_DISCONNECTED = 2;
const int WL_CONNECTED = 3;
const int WL_IDLE_STATUS = 4;

namespace detail
{
struct wifi
{
    void begin(const byte*, const byte*)
    {}
    
    int status() const
    {
        return 0;
    }
    
    int RSSI() const
    {
        return 0;
    }
};
}

struct WiFiClient
{
    bool connected() const
    {
        return true;
    }
    
    bool available() const
    {
        return true;
    }
    
    bool connect(const byte*, int)
    {
        return true;
    }
    
    void write(const byte*, size_t)
    {}
    
    byte read()
    {
        return 0;
    }
    
    void stop()
    {}
};

detail::wifi WiFi;