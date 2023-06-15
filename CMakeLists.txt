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
  include_directories(${CMAKE_SOURCE_DIR})

  add_executable(type_traits_test "test/type_traits_unittest.cc")
  target_link_libraries(type_traits_test gmock gtest gtest_main)
  
  add_executable(memory_test "test/memory_unittest.cc")
  target_link_libraries(memory_test gmock gtest gtest_main)

  add_executable(utility_test "test/utility_unittest.cc")
  target_link_libraries(utility_test gmock gtest gtest_main)

  add_test(NAME "type_traits_test" COMMAND "type_traits_test")
  add_test(NAME "memory_test" COMMAND "memory_test")
  add_test(NAME "utility_test" COMMAND "utility_test")
endif(TINY_STL_BUILD_TESTS)
