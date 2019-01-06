#pragma once

template<typename First, typename... Rest>
struct tuple: public tuple<Rest...> 
{
  First first;
  tuple(First first, Rest... rest): tuple<Rest...>(rest...), first(first) {}
};

template<typename First>
struct tuple<First> 
{
  First first;
  tuple(First first): first(first) {}
};

template<int index, typename First, typename... Rest>
struct GetImpl 
{
  static auto value(const tuple<First, Rest...>* t) -> decltype(GetImpl<index - 1, Rest...>::value(t)) 
  {
    return GetImpl<index - 1, Rest...>::value(t);
  }
};

template<typename First, typename... Rest>
struct GetImpl<0, First, Rest...> 
{
  static First value(const tuple<First, Rest...>* t) 
  {
    return t->first;
  }
};

template<int index, typename First, typename... Rest>
auto get(const tuple<First, Rest...>& t) -> decltype(GetImpl<index, First, Rest...>::value(&t)) 
{ 
  return GetImpl<index, First, Rest...>::value(&t);
}