// Observable Library
// Copyright (c) 2016-present David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef OBS_OBSERVERS_H_INCLUDED
#define OBS_OBSERVERS_H_INCLUDED
#pragma once

#include "obs/lists.h"

namespace obs {

template<typename T, template<typename> class List = default_list>
class observers {
public:
  using observer_type = T;
  using list_type = List<observer_type>;
  using iterator = typename list_type::iterator;

  bool empty() const { return m_observers.empty(); }
  std::size_t size() const { return m_observers.size(); }

  void add_observer(observer_type* observer) {
    m_observers.push_back(observer);
  }

  void remove_observer(observer_type* observer) {
    m_observers.erase(observer);
  }

  template<typename ...Args>
  void notify_observers(void (observer_type::*method)(Args...), Args ...args) {
#ifdef _DEBUG
    Iterating<list_type> flag(m_observers);
#endif
    for (auto observer : m_observers) {
      if (observer)
        (observer->*method)(std::forward<Args>(args)...);
    }
  }

private:
  list_type m_observers;
};

template<typename T>
using fast_observers = observers<T, fast_list>;

template<typename T>
using safe_observers = observers<T, safe_list>;

} // namespace obs

#endif
