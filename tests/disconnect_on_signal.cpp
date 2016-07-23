// Observable Library
// Copyright (c) 2016 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include "obs/signal.h"
#include "test.h"

using namespace obs;

class A {
public:
  A(signal<void()>& sig) {
    m_conn = sig.connect(&A::on_signal, this);
  }

private:
  void on_signal() {
    m_conn.disconnect();
  }

  connection m_conn;
};

int main() {
  signal<void()> signal;
  {
    A a(signal);
    signal();
  }
  signal();
}
