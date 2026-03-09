// Observable Library
// Copyright (c) 2016-present David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef OBS_SIGNAL_H_INCLUDED
#define OBS_SIGNAL_H_INCLUDED
#pragma once

#include "obs/connection.h"
#include "obs/lists.h"
#include "obs/slot.h"

#include <functional>
#include <type_traits>

namespace obs {

class signal_base {
public:
  virtual ~signal_base() { }
  virtual void disconnect_slot(slot_base* slot) = 0;
};

// Signal for any kind of functions
template<typename Callable, template<typename> class List = default_list>
class signal { };

template<typename R, typename...Args, template<typename> class List>
class signal<R(Args...), List> : public signal_base {
public:
  using result_type = R;
  using slot_type = slot<R(Args...)>;
  using slot_list = List<slot_type>;

  signal() { }
  ~signal() {
    for (auto slot : m_slots)
      delete slot;
  }

  signal(const signal&) { }
  signal& operator=(const signal&) { return *this; }

  operator bool() const { return !m_slots.empty(); }

  connection add_slot(slot_type* s) {
    m_slots.push_back(s);
    return connection(this, s);
  }

  template<typename Function>
  connection connect(Function&& f) {
    return add_slot(new slot_type(std::forward<Function>(f)));
  }

  template<class Class>
  connection connect(result_type (Class::*m)(Args...args), Class* t) {
    return add_slot(new slot_type(
                      [=](Args...args) -> result_type {
                        return (t->*m)(std::forward<Args>(args)...);
                      }));
  }

  virtual void disconnect_slot(slot_base* slot) override {
    m_slots.erase(static_cast<slot_type*>(slot));
  }

  template<typename U = R, typename...Args2>
  typename std::enable_if<std::is_void<U>::value, void>::type
  operator()(Args2&&...args) {
    for (auto slot : m_slots)
      if (slot)
        (*slot)(std::forward<Args2>(args)...);
  }

  template<typename U = R, typename...Args2>
  typename std::enable_if<!std::is_void<U>::value, U>::type
  operator()(Args2&&...args) {
    U result = {};
    for (auto slot : m_slots)
      if (slot)
        result = (*slot)(std::forward<Args2>(args)...);
    return result;
  }

protected:
  slot_list m_slots;
};

template<typename Callable>
using fast_signal = signal<Callable, fast_list>;

template<typename Callable>
using safe_signal = signal<Callable, safe_list>;

} // namespace obs

#endif
