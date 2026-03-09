// Observable Library
// Copyright (c) 2016-present David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include "obs/signal.h"
#include "test.h"

class A {
public:
  A(obs::safe_signal<void()>& sig) {
    m_conn = sig.connect(&A::on_signal, this);
  }

private:
  void on_signal() {
    m_conn.disconnect();
  }

  obs::connection m_conn;
};

int main() {
  // We use the "safe" version because the fast one doesn't support
  // disconnections from the same signal.
  obs::safe_signal<void()> signal;
  {
    A a(signal);
    signal();
  }
  signal();
}
