cmake_minimum_required(VERSION 3.23)
project(jute_editor)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

cmake_path(GET CMAKE_BINARY_DIR FILENAME REL_BINARY_DIR)
set(J_ENGINE_DLL_REL_DIR ../libjute-engine/${REL_BINARY_DIR})
set(J_ENGINE_H_REL_DIR ../libjute-engine)

link_directories(${J_ENGINE_DLL_REL_DIR})
include_directories(${J_ENGINE_H_REL_DIR})

add_executable(jute_editor jute/editor/core/editor.cpp)
target_link_libraries(jute_editor jute_engine)

add_custom_command(TARGET jute_editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/${J_ENGINE_DLL_REL_DIR}/libjute_engine.dll"
        $<TARGET_FILE_DIR:jute_editor>)
