#pragma once

#include "vector.hpp"

template <typename T, size_t Capacity>
class ring
{
  array<T, Capacity> data_;
  size_t cursor_ =  0;

public:

  ring()
  {
    data_.reserve(Capacity);
  }

  T& operator[](size_t i)
  {
    return data_[i];
  }

  T& next()
  {
    return data_[cursor_++ % Capacity];
  }

  size_t size() const
  {
    return Capacity;
  }
};
