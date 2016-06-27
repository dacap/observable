// Observable Library
// Copyright (c) 2016 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef OBS_SIGNAL_H_INCLUDED
#define OBS_SIGNAL_H_INCLUDED
#pragma once

#include "obs/connection.h"
#include "obs/safe_list.h"
#include "obs/slot.h"

namespace obs {

class signal_base {
public:
  virtual ~signal_base() { }
  virtual void disconnect_slot(slot_base* slot) = 0;
};

// signal0_base<R> - Base class to delegate responsibility to
// functions of zero arguments.
template<typename R>
class signal0_base : public signal_base {
public:
  typedef R return_type;
  typedef slot0<R> slot_type;
  typedef safe_list<slot_type> slot_list;

  signal0_base() { }
  ~signal0_base() {
    for (auto slot : m_slots)
      delete slot;
  }

  signal0_base(const signal0_base&) { }
  signal0_base operator=(const signal0_base&) {
    return *this;
  }

  connection add_slot(slot_type* s) {
    m_slots.push_back(s);
    return connection(this, s);
  }

  template<typename F>
  connection connect(const F& f) {
    return add_slot(new slot0_fun<R, F>(f));
  }

  template<class T>
  connection connect(R (T::*m)(), T* t) {
    return add_slot(new slot0_mem<R, T>(m, t));
  }

  virtual void disconnect_slot(slot_base* slot) override {
    m_slots.erase(static_cast<slot_type*>(slot));
  }

protected:
  slot_list m_slots;
};

// signal0<R>
template<typename R>
class signal0 : public signal0_base<R> {
public:
  // GCC needs redefinitions
  typedef signal0_base<R> base;
  typedef slot0<R> slot_type;
  typedef typename base::slot_list slot_list;

  signal0() {
  }

  R operator()(R default_result = R()) {
    R result(default_result);
    for (auto slot : base::m_slots)
      if (slot)
        result = (*slot)();
    return result;
  }

  template<typename Merger>
  R operator()(R default_result, const Merger& m) {
    R result(default_result);
    Merger merger(m);
    for (auto slot : base::m_slots)
      if (slot)
        result = merger(result, (*slot)());
    return result;
  }

};

// signal0<void>
template<>
class signal0<void> : public signal0_base<void> {
public:
  // GCC needs redefinitions
  typedef signal0_base<void> base;
  typedef slot0<void> slot_type;
  typedef base::slot_list slot_list;

  signal0() { }

  void operator()() {
    for (auto slot : base::m_slots)
      if (slot)
        (*slot)();
  }

};

// signal1_base<R, A1> - base class to delegate responsibility to
// functions of one argument.
template<typename R, typename A1>
class signal1_base : public signal_base {
public:
  typedef R return_type;
  typedef slot1<R, A1> slot_type;
  typedef safe_list<slot_type> slot_list;

  signal1_base() { }
  ~signal1_base() {
    for (auto slot : m_slots)
      delete slot;
  }

  signal1_base(const signal1_base&) { }
  signal1_base operator=(const signal1_base&) {
    return *this;
  }

  connection add_slot(slot_type* slot) {
    m_slots.push_back(slot);
    return connection(this, slot);
  }

  template<typename F>
  connection connect(const F& f) {
    return add_slot(new slot1_fun<R, F, A1>(f));
  }

  template<class T>
  connection connect(R (T::*m)(A1), T* t) {
    return add_slot(new slot1_mem<R, T, A1>(m, t));
  }

  virtual void disconnect_slot(slot_base* slot) override {
    m_slots.erase(static_cast<slot_type*>(slot));
  }

protected:
  slot_list m_slots;
};

// signal1<R, A1>
template<typename R, typename A1>
class signal1 : public signal1_base<R, A1> {
public:
  // GCC needs redefinitions
  typedef signal1_base<R, A1> base;
  typedef slot1<R, A1> slot_type;
  typedef typename base::slot_list slot_list;

  signal1() { }

  R operator()(A1 a1, R default_result = R()) {
    R result(default_result);
    for (auto slot : base::m_slots)
      if (slot)
        result = (*slot)(a1);
    return result;
  }

  template<typename Merger>
  R operator()(A1 a1, R default_result, const Merger& m) {
    R result(default_result);
    Merger merger(m);
    for (auto slot : base::m_slots)
      if (slot)
        result = merger(result, (*slot)(a1));
    return result;
  }

};

// signal1<void, A1>
template<typename A1>
class signal1<void, A1> : public signal1_base<void, A1>
{
public:
  // GCC needs redefinitions
  typedef signal1_base<void, A1> base;
  typedef slot1<void, A1> slot_type;
  typedef typename base::slot_list slot_list;

  signal1() { }

  void operator()(A1 a1) {
    for (auto slot : base::m_slots)
      if (slot)
        (*slot)(a1);
  }

};

// signal2_base<R, A1, A2> - base class to delegate responsibility to
// functions of two arguments.
template<typename R, typename A1, typename A2>
class signal2_base : public signal_base {
public:
  typedef R return_type;
  typedef slot2<R, A1, A2> slot_type;
  typedef safe_list<slot_type> slot_list;

  signal2_base() { }
  ~signal2_base() {
    for (auto slot : m_slots)
      delete slot;
  }

  signal2_base(const signal2_base&) { }
  signal2_base operator=(const signal2_base&) {
    return *this;
  }

  connection add_slot(slot_type* slot) {
    m_slots.push_back(slot);
    return connection(this, slot);
  }

  template<typename F>
  connection connect(const F& f) {
    return add_slot(new slot2_fun<R, F, A1, A2>(f));
  }

  template<class T>
  connection connect(R (T::*m)(A1, A2), T* t) {
    return add_slot(new slot2_mem<R, T, A1, A2>(m, t));
  }

  virtual void disconnect_slot(slot_base* slot) override {
    m_slots.erase(static_cast<slot_type*>(slot));
  }

protected:
  slot_list m_slots;
};

// signal2<R, A1>
template<typename R, typename A1, typename A2>
class signal2 : public signal2_base<R, A1, A2> {
public:
  // GCC needs redefinitions
  typedef signal2_base<R, A1, A2> base;
  typedef slot2<R, A1, A2> slot_type;
  typedef typename base::slot_list slot_list;

  signal2() {
  }

  R operator()(A1 a1, A2 a2, R default_result = R()) {
    R result(default_result);
    for (auto slot : base::m_slots)
      if (slot)
        result = (*slot)(a1, a2);
    return result;
  }

  template<typename Merger>
  R operator()(A1 a1, A2 a2, R default_result, const Merger& m) {
    R result(default_result);
    Merger merger(m);
    for (auto slot : base::m_slots)
      if (slot)
        result = merger(result, (*slot)(a1, a2));
    return result;
  }

};

// signal2<void, A1>
template<typename A1, typename A2>
class signal2<void, A1, A2> : public signal2_base<void, A1, A2> {
public:
  // GCC needs redefinitions
  typedef signal2_base<void, A1, A2> base;
  typedef slot2<void, A1, A2> slot_type;
  typedef typename base::slot_list slot_list;

  signal2() {
  }

  void operator()(A1 a1, A2 a2) {
    for (auto slot : base::m_slots)
      if (slot)
        (*slot)(a1, a2);
  }

};

} // namespace obs

#endif
