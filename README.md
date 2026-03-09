Observable Library
==================

*Copyright (C) 2016-present David Capello*

[![build](https://github.com/dacap/observable/actions/workflows/build.yml/badge.svg)](https://github.com/dacap/observable/actions/workflows/build.yml)
[![MIT Licensed](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE.txt)

Library to use the observer pattern in C++11 programs with
observable/observer classes or signals/slots.

Features
--------

* Generate an observable notification/signal from multiple threads
* Add/remove observers/slots from multiple threads
* Erase/disconnect an observer/slot from the same observable notification/signal
* Reconnect an observer in the same notification

Observable
----------

An observable `Widget`:

```cpp
#include "obs.h"

class WidgetObserver {
public:
  virtual ~WidgetObserver() = 0;
  virtual void onClick() { }
};

class Widget : public obs::observable<WidgetObserver> {
public:
  void processClick() {
    notify_observers(&WidgetObserver::onClick);
  }
};
```

An example

```cpp
#include "obs.h"

class ObserveClick : public WidgetObserver {
public:
  void onClick() override {
    // Do something...
  }
};

...
ObserveClick observer;
Widget button;
button.add_observer(&observer);
```

Signal
------

```cpp
#include "obs.h"

int main() {
  obs::signal<void (int, int)> sig;
  sig.connect([](int x, int y){ ... });
  sig(1, 2); // Generate signal
}
```

Safe vs Fast
----------------

There are two variants of signals and observers:

* `obs::safe_signal` vs `obs::fast_signal`
* `obs::safe_observers` vs `obs::fast_observers`

The only difference between both is that the "fast" version uses
`obs::fast_list` instead of `obs::safe_list`, where the former keeps
track of slots with a `std::vector` and the later one is a thread-safe
version list to connect/disconnect slots from different threads.

By default and for backward compatibility, `obs::signal` and
`obs::observers` use the safe version, but you can enable the
`OBSERVABLE_FAST_LIST` option to switch from `obs::safe_list` to
`obs::fast_list` which is recommended for most cases (e.g. you don't
need to do strange connections/disconnections as in [tests](tests)).
