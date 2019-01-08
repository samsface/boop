#pragma once

#include <queue>

using byte = char;

const int OUTPUT = 0;
const int INPUT_PULLUP = 1;
const int LED_BUILTIN = 2;
const byte LOW = 0;
const byte HIGH = 1;

namespace detail
{
struct pin
{
    std::queue<byte> data;
    
    void write(byte b)
    {
        data.push(b);
    }
    
    template<typename Array>
    void write(Array bytes)
    {
        for(auto i = 0; i < bytes.size(); i++)
        {
            write(bytes[i]);
        }
    }
    
    int read()
    {
        if(data.empty()) return -1;
     
        auto b = data.front();
        data.pop();
        return b;
        
    }
};
    
struct arduino
{
    std::array<pin, 12> pins;
    long clock = 0;
};
    
struct hardware_serial
{
    arduino& arduino_;
    
    hardware_serial(arduino& a) : arduino_{a}
    {
        
    }
    
    void begin(int)
    {}
        
    bool available() const
    {
        return !arduino_.pins[0].data.empty();
    }
        
    void write(const byte* b, size_t len)
    {
        for(auto i = 0; i < len; i++)
        {
            arduino_.pins[1].write(b[i]);
        }
    }
        
    int read()
    {
        return arduino_.pins[0].read();
    }
};
}

detail::arduino arduino;
detail::hardware_serial Serial{arduino};

void pinMode(int, int)
{}

byte digitalRead(int p)
{
    return arduino.pins[p].data.empty() ? HIGH : arduino.pins[p].data.front();
}

void digitalWrite(int, int)
{}

void analogWrite(int, int)
{}


long millis()
{
    return arduino.clock;
}

long random(long min, long max)
{
    return 0;
}

void delay(int)
{}




