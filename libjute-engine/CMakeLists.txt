cmake_minimum_required(VERSION 3.23)
project(libjute_engine)

set(CMAKE_CXX_STANDARD 23)

include_directories(. ./vendor)

link_directories(vendor/lib)

add_library(jute_engine SHARED libjute/engine/core/engine.cpp libjute/engine/core/logger.cpp)
target_link_libraries(jute_engine PRIVATE spdlog)
target_compile_definitions(jute_engine
        PRIVATE -DLIBJUTE_ENGINE_EXPORT
        PUBLIC $<$<CONFIG:Debug>:LIBJUTE_ENGINE_SET_LOGGER_LEVEL_TRACE>
        PUBLIC $<$<CONFIG:Release>:LIBJUTE_ENGINE_SET_LOGGER_LEVEL_ERROR>)

add_executable(test_basic tests/basic/main.cpp)
