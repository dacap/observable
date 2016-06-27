// Observable Library
// Copyright (c) 2016 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef OBS_SLOT_H_INCLUDED
#define OBS_SLOT_H_INCLUDED
#pragma once

namespace obs {

class slot_base {
public:
  slot_base() { }
  virtual ~slot_base() { }

  // Disable copy
  slot_base(const slot_base&) = delete;
  slot_base& operator=(const slot_base&) = delete;
};

// slot0 - Base class for delegates of zero arguments.
template<typename R>
class slot0 : public slot_base {
public:
  slot0() { }
  slot0(const slot0& s) { (void)s; }
  virtual ~slot0() { }
  virtual R operator()() = 0;
};

// slot0_fun - hold a F instance and use the function call operator
template<typename R, typename F>
class slot0_fun : public slot0<R> {
  F f;
public:
  slot0_fun(const F& f) : f(f) { }
  slot0_fun(const slot0_fun& s) : slot0<R>(s), f(s.f) { }
  ~slot0_fun() { }
  R operator()() { return f(); }
};

template<typename F>
class slot0_fun<void, F> : public slot0<void> {
  F f;
public:
  slot0_fun(const F& f) : f(f) { }
  slot0_fun(const slot0_fun& s) : slot0<void>(s), f(s.f) { }
  ~slot0_fun() { }
  void operator()() { f(); }
};

// slot0_mem - pointer to a member function of the T class
template<typename R, class T>
class slot0_mem : public slot0<R> {
  R (T::*m)();
  T* t;
public:
  slot0_mem(R (T::*m)(), T* t) : m(m), t(t) { }
  slot0_mem(const slot0_mem& s) : slot0<R>(s), m(s.m), t(s.t) { }
  ~slot0_mem() { }
  R operator()() { return (t->*m)(); }
};

template<class T>
class slot0_mem<void, T> : public slot0<void> {
  void (T::*m)();
  T* t;
public:
  slot0_mem(void (T::*m)(), T* t) : m(m), t(t) { }
  slot0_mem(const slot0_mem& s) : slot0<void>(s), m(s.m), t(s.t) { }
  ~slot0_mem() { }
  void operator()() { (t->*m)(); }
};

// slot1 - Base class for delegates of one argument.
template<typename R, typename A1>
class slot1 : public slot_base {
public:
  slot1() { }
  slot1(const slot1& s) { (void)s; }
  virtual ~slot1() { }
  virtual R operator()(A1 a1) = 0;
};

// slot1_fun - hold a F instance and use the function call operator
template<typename R, typename F, typename A1>
class slot1_fun : public slot1<R, A1> {
  F f;
public:
  slot1_fun(const F& f) : f(f) { }
  slot1_fun(const slot1_fun& s) : slot1<R, A1>(s), f(s.f) { }
  ~slot1_fun() { }
  R operator()(A1 a1) { return f(a1); }
};

template<typename F, typename A1>
class slot1_fun<void, F, A1> : public slot1<void, A1> {
  F f;
public:
  slot1_fun(const F& f) : f(f) { }
  slot1_fun(const slot1_fun& s) : slot1<void, A1>(s), f(s.f) { }
  ~slot1_fun() { }
  void operator()(A1 a1) { f(a1); }
};

// slot1_mem - pointer to a member function of the T class
template<typename R, class T, typename A1>
class slot1_mem : public slot1<R, A1> {
  R (T::*m)(A1);
  T* t;
public:
  slot1_mem(R (T::*m)(A1), T* t) : m(m), t(t) { }
  slot1_mem(const slot1_mem& s) : slot1<R, A1>(s), m(s.m), t(s.t) { }
  ~slot1_mem() { }
  R operator()(A1 a1) { return (t->*m)(a1); }
};

template<class T, typename A1>
class slot1_mem<void, T, A1> : public slot1<void, A1> {
  void (T::*m)(A1);
  T* t;
public:
  slot1_mem(void (T::*m)(A1), T* t) : m(m), t(t) { }
  slot1_mem(const slot1_mem& s) : slot1<void, A1>(s), m(s.m), t(s.t) { }
  ~slot1_mem() { }
  void operator()(A1 a1) { (t->*m)(a1); }
};

// slot2 - Base class for delegates of two arguments.
template<typename R, typename A1, typename A2>
class slot2 : public slot_base {
public:
  slot2() { }
  slot2(const slot2& s) { (void)s; }
  virtual ~slot2() { }
  virtual R operator()(A1 a1, A2 a2) = 0;
};

// slot2_fun - hold a F instance and use the function call operator
template<typename R, typename F, typename A1, typename A2>
class slot2_fun : public slot2<R, A1, A2> {
  F f;
public:
  slot2_fun(const F& f) : f(f) { }
  slot2_fun(const slot2_fun& s) : slot2<R, A1, A2>(s), f(s.f) { }
  ~slot2_fun() { }
  R operator()(A1 a1, A2 a2) { return f(a1, a2); }
};

template<typename F, typename A1, typename A2>
class slot2_fun<void, F, A1, A2> : public slot2<void, A1, A2> {
  F f;
public:
  slot2_fun(const F& f) : f(f) { }
  slot2_fun(const slot2_fun& s) : slot2<void, A1, A2>(s), f(s.f) { }
  ~slot2_fun() { }
  void operator()(A1 a1, A2 a2) { f(a1, a2); }
};

// slot2_mem - pointer to a member function of the T class
template<typename R, class T, typename A1, typename A2>
class slot2_mem : public slot2<R, A1, A2> {
  R (T::*m)(A1, A2);
  T* t;
public:
  slot2_mem(R (T::*m)(A1, A2), T* t) : m(m), t(t) { }
  slot2_mem(const slot2_mem& s) : slot2<R, A1, A2>(s), m(s.m), t(s.t) { }
  ~slot2_mem() { }
  R operator()(A1 a1, A2 a2) { return (t->*m)(a1, a2); }
};

template<class T, typename A1, typename A2>
class slot2_mem<void, T, A1, A2> : public slot2<void, A1, A2> {
  void (T::*m)(A1, A2);
  T* t;
public:
  slot2_mem(void (T::*m)(A1, A2), T* t) : m(m), t(t) { }
  slot2_mem(const slot2_mem& s) : slot2<void, A1, A2>(s), m(s.m), t(s.t) { }
  ~slot2_mem() { }
  void operator()(A1 a1, A2 a2) { return (t->*m)(a1, a2); }
};

} // namespace obs

#endif
