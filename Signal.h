#pragma once

#include "Vector.h"
#include "Callbacks.h"

#define SLOT(...) (void(Callable::*)(__VA_ARGS__))&

template<typename ... Args>
class Signal {
public:
  void emit(Args ... param) const;

  void connect(void(*func)(Args ...));
  void connect(void* obj, void(Callable::* func)(Args ...));

  void disconnect(void(*func)(Args ...));
  void disconnect(void* obj);
  void disconnect(void* obj, void(Callable::* func)(Args ...));

private:
  Vector<s_objCallback<Args ...>> m_objCallbacks;
  Vector<s_callback<Args ...>> m_callbacks;
};



template<typename ... Args>
void Signal<Args ...>::emit(Args ... param) const
{
  for (int i = 0; i < m_callbacks.size(); i++)
    m_callbacks[i].func(param ...);

  for (int i = 0; i < m_objCallbacks.size(); i++)
    ((Callable*)m_objCallbacks[i].obj->*m_objCallbacks[i].func)(param ...);
}

template<typename ... Args>
void Signal<Args ...>::connect(void(*func)(Args ...))
{
  struct s_callback<Args ...> callback;
  callback.func = func;

  if (m_callbacks.contains(callback)) return;
  m_callbacks << callback;
}

template<typename ... Args>
void Signal<Args ...>::connect(void* obj, void(Callable::* func)(Args ...))
{
  struct s_objCallback<Args ...> callback;
  callback.obj = (Callable*)obj;
  callback.func = func;

  if (m_objCallbacks.contains(callback)) return;
  m_objCallbacks << callback;
}

template<typename ... Args>
void Signal<Args ...>::disconnect(void(*func)(Args ...))
{
  struct s_callback<Args ...> callback;
  callback.func = func;
  m_callbacks.removeAll(callback);
}

template<typename ... Args>
void Signal<Args ...>::disconnect(void* obj, void(Callable::* func)(Args ...))
{
  struct s_objCallback<Args ...> callback;
  callback.obj = obj;
  callback.func = func;
  m_objCallbacks.removeAll(callback);
}

template<typename ... Args>
void Signal<Args ...>::disconnect(void* obj)
{
  struct s_objCallback<Args ...> callback;
  callback.obj = obj;
  callback.func = nullptr;
  m_objCallbacks.removeAll(callback);
}