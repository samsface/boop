#pragma once

template <typename T, size_t Capacity>
class array
{
  T data_[Capacity];
  size_t size_;
  
public:

  array() : data_{}, size_{ 0 }
  {
  }

        T& operator[](size_t i)       { return data_[i]; }
  const T& operator[](size_t i) const { return data_[i]; }
    

  T& front() { return data_[0]; }
        
  void push_back(T i)
  {
    if(size_ < Capacity)
    {
      data_[size_] = i;
      size_++;
    }
  }

  void pop_front()
  {
    data_[0] = T{};
    
    if(size_ > 0)
    {
      memmove(&data_[0], &data_[1], (size_-1)*sizeof(T));
    }
    
    size_--;
  }

  bool empty() const
  {
    return size_ == 0;
  }

  size_t size() const
  {
    return size_;
  }

  void clear()
  {
    while(!empty())
    {
      data_[--size_] = T{};
    }
  }

  void reserve(size_t s)
  {
    while(size_ < s) size_++;
  }
};
