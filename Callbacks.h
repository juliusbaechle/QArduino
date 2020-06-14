#pragma once

class Callable {};

template<typename ... Args>
struct s_objCallback
{
  void* obj;
  void(Callable::*func)(Args ...);

  bool operator==(s_objCallback callback2)
  {
    if (obj != callback2.obj) return false;
    if (func != callback2.func && callback2.func != nullptr) return false;
    return true;
  }
};

template<typename ... Args>
struct s_callback
{
  void(*func)(Args ...);

  bool operator==(s_callback callback2)
  {
    if (func != callback2.func) return false;
    return true;
  }
};
