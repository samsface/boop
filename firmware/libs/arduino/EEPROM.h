#pragma once

#include <array>
#include <Arduino.h>

template<size_t Size>
struct eeprom
{
    std::array<byte, Size> data_;
    
    template<typename T>
    void get(int address, T& t)
    {
        T* tp = &t;
        tp = reinterpret_cast<T*>(&data_[address]);
    }
    
    template<typename T>
    void put(int address, const T& t)
    {
        auto b = reinterpret_cast<const byte*>(&t);
        
        for(auto i = 0; i < sizeof(t); i++)
        {
            data_[address + i] = b[i];
        }
    }
    
    void write(int address, byte b)
    {
        data_[address] = b;
    }
    
    size_t length()
    {
        return Size;
    }
};

eeprom<128> EEPROM;