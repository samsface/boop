#pragma once

using byte = uint8_t;

const int WL_CONNECT_FAILED = 0;
const int WL_CONNECTION_LOST = 1;
const int WL_DISCONNECTED = 2;
const int WL_CONNECTED = 3;

namespace detail
{
struct wifi
{
    void begin(const byte*, const byte*)
    {}
    
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
    
    int status() const
    {
        return 0;
    }
    
    void connect(const byte*, int)
    {}
    
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