// Observable Library
// Copyright (c) 2016 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include "obs/signal.h"

using namespace obs;

int main() {
  signal<void(int)> s;
  connection c = s.connect(
    [&](int i){
      if (i > 0)
        s(i-1);
      else
        c.disconnect();
    });
  s(5);
}
