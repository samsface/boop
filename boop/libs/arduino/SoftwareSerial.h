#pragma once

using byte = uint8_t;

struct SoftwareSerial
{
    SoftwareSerial(int, int)
    {}
    
    void begin(int)
    {}
    
    bool available() const
    {
        return true;
    }
    
    void write(const byte*, size_t)
    {}
    
    byte read()
    {
        return 0;
    }
};
