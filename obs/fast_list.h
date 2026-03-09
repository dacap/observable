// Observable Library
// Copyright (c) 2026-present David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef OBS_FAST_LIST_H_INCLUDED
#define OBS_FAST_LIST_H_INCLUDED
#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

namespace obs {

template<typename T>
class fast_list {
  std::vector<T*> m_list;
#ifndef NDEBUG
  int m_iterating = 0;
#endif

public:
  using iterator = typename std::vector<T*>::iterator;

  fast_list() = default;
  ~fast_list() = default;

  bool empty() const { return m_list.empty(); }
  iterator begin() { return m_list.begin(); }
  iterator end() { return m_list.end(); }

  void push_back(T* value) {
    m_list.push_back(value);
  }

  void erase(T* value) {
    assert(m_iterating == 0);
    auto it = std::find(m_list.begin(), m_list.end(), value);
    if (it != m_list.end())
      m_list.erase(it);
  }

#ifndef NDEBUG
  void set_iterating(const bool state) {
    if (state)
      ++m_iterating;
    else
      --m_iterating;
  }
#endif

};

} // namespace obs

#endif
