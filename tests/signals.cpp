// Observable Library
// Copyright (c) 2016 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include "obs/signal.h"
#include "test.h"

using namespace obs;

int main() {
  {
    signal0<void> sig;
    int x = 2;
    sig.connect([&x](){ ++x; });
    EXPECT_EQ(x, 2);
    sig();
    EXPECT_EQ(x, 3);
    sig();
    EXPECT_EQ(x, 4);
  }

  {
    signal1<void, int> sig;
    int x = 2;
    sig.connect([&x](int y){ x += y; });
    sig(3);
    sig(4);
    EXPECT_EQ(x, 9);
  }

  {
    signal2<void, int, int> sig;
    int c = 0;
    sig.connect([&](int x, int y){ c = x+y; });
    sig(3, 4);
    EXPECT_EQ(c, 7);
  }
}
