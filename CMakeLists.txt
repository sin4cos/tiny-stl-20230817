cmake_minimum_required(VERSION 3.9)

project(tiny-stl VERSION 0.0.1 LANGUAGES CXX)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

option(TINY_STL_BUILD_TESTS "Build Tiny-STL's unit tests" ON)

if(TINY_STL_BUILD_TESTS)
  enable_testing()
  add_subdirectory("third_party/googletest")
endif(TINY_STL_BUILD_TESTS)
