#pragma once

template <typename T>
class optional
{
  T t_;
  bool value_ = false;

public:

  optional() = default;

  template<typename ...Args>
  optional(Args ...args) : t_{ args... }, value_{ true }
  {}

  explicit operator bool() const { return value_; }

  const T* operator->() const { return &t_; }

  const T& value() const { return t_; }
};
