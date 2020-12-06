cmake_minimum_required(VERSION 3.5)
project(Decode)

set(CMAKE_CXX_STANDARD 17)

add_executable(Decode
  main.cpp
  daunit.cpp
  daunit.h
  dadecoder.cpp
  dadecoder.h)