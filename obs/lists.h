// Observable Library
// Copyright (c) 2026-present David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef OBS_LISTS_H_INCLUDED
#define OBS_LISTS_H_INCLUDED
#pragma once

#include "obs/fast_list.h"
#include "obs/safe_list.h"

namespace obs {

#ifdef OBSERVABLE_FAST_LIST
  template<typename T>
  using default_list = fast_list<T>;
#else
  template<typename T>
  using default_list = safe_list<T>;
#endif

} // namespace obs

#endif
