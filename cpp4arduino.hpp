// cpp4arduino.cpp
// Standard C++ functions missing in Arduino
// cpp4arduino.com
// https://gist.github.com/IvanVergiliev/9639530

#ifndef _CPP_4_ARDUINO
#define _CPP_4_ARDUINO

namespace cpp4arduino
{

template <class T>
struct remove_reference
{
  typedef T type;
};

template <class T>
struct remove_reference<T &>
{
  typedef T type;
};

template <class T>
struct remove_reference<T &&>
{
  typedef T type;
};

template <typename T>
constexpr typename remove_reference<T>::type &&move(T &&x) noexcept
{
  return static_cast<typename remove_reference<T>::type &&>(x);
}

template<typename First, typename... Rest>
struct Tuple: public Tuple<Rest...>
{
  Tuple(First first, Rest... rest): Tuple<Rest...>(rest...), first(first) {}

  First first;
};

template<typename First>
struct Tuple<First>
{
  Tuple(First first): first(first) {}

  First first;
};

template<int index, typename First, typename... Rest>
struct GetImpl
{
  static auto value(const Tuple<First, Rest...>* t) -> decltype(GetImpl<index - 1, Rest...>::value(t)) {
    return GetImpl<index - 1, Rest...>::value(t);
  }
};

template<typename First, typename... Rest>
struct GetImpl<0, First, Rest...> {
  static First value(const Tuple<First, Rest...>* t) {
    return t->first;
  }
};

template<int index, typename First, typename... Rest>
auto get(const Tuple<First, Rest...>& t) -> decltype(GetImpl<index, First, Rest...>::value(&t)) {
  return GetImpl<index, First, Rest...>::value(&t);
}

}  // namespace cpp4arduino

#include "new"

#if __cpp_sized_deallocation

void operator delete(void* ptr, size_t) {
    delete ptr;
}

void operator delete[](void* ptr, size_t) {
    delete[] ptr;
}

#endif

#endif  // _CPP_4_ARDUINO
