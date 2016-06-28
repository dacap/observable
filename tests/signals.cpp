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
    signal<void()> sig;
    int c = 0;
    sig.connect([&](){ ++c; });
    sig.connect([&](){ ++c; });
    sig();
    sig();
    EXPECT_EQ(c, 4);
  }

  {
    signal<int()> sig;
    sig.connect([](){ return 1; });
    sig.connect([](){ return 4; });
    int res = sig();
    EXPECT_EQ(res, 4);
  }

  {
    int a=0, b=0;
    double c=0.0;
    signal<void(int, int, double)> sig;
    sig.connect([&](int x, int y, double z) {
                  a = x;
                  b = y;
                  c = z;
                });
    sig(1, 2, 3.4);
    EXPECT_EQ(1, a);
    EXPECT_EQ(2, b);
    EXPECT_EQ(3.4, c);
  }

  // Alternative signal sintax

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
