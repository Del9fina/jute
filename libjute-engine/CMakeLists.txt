cmake_minimum_required(VERSION 3.23)
project(libjute_engine)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_library(jute_engine SHARED libjute/engine/core/engine.cpp)
target_compile_definitions(jute_engine PUBLIC -DJ_EXPORT)

add_executable(test_basic tests/basic/main.cpp)
