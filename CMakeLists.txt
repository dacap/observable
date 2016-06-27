# Observable Library
# Copyright (C) 2016 David Capello

cmake_minimum_required(VERSION 2.8)

project(observable CXX)
option(OBSERVABLE_TESTS "Compile observable tests" on)

include_directories(.)

if(UNIX)
  add_definitions(-std=c++11)
  if(NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
  endif()
endif()

add_library(obs obs/connection.cpp)

if(OBSERVABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
