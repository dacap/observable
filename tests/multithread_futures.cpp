// Observable Library
// Copyright (c) 2018 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include "obs/signal.h"
#include "test.h"

#include <future>
#include <thread>
#include <vector>

using namespace obs;

int main() {
  obs::signal<double()> sig;

  auto context =
    [&sig](){
      double count = 0.0;
      for (int i=0; i<64; ++i) {
        std::vector<obs::scoped_connection> conns(256);
        for (auto& conn : conns)
          conn = sig.connect([](){ return 1.0; });
        count += sig();
      }
      return count;
    };

  std::vector<std::future<double>> futures;
  for (int i = std::thread::hardware_concurrency() / 2; i > 0; --i)
    futures.emplace_back(std::async(std::launch::async, context));
  for (auto& f : futures)
    f.get();
  return 0;
}
