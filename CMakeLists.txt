# Observable Library
# Copyright (C) 2016-present David Capello

cmake_minimum_required(VERSION 3.15)

project(observable CXX)
option(OBSERVABLE_TESTS "Compile observable tests" ON)
option(OBSERVABLE_BENCHMARKS "Compile observable benchmarks" OFF)
option(OBSERVABLE_FAST_LIST "Use fast list (non-thread safe) instead of safe (thread-safe) one by default" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX AND NOT APPLE)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
endif()

add_library(obs obs/connection.cpp)
target_include_directories(obs PUBLIC .)

if(OBSERVABLE_FAST_LIST)
  target_compile_definitions(obs PUBLIC OBSERVABLE_FAST_LIST)
endif()

if(OBSERVABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(OBSERVABLE_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()
