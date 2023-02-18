cmake_minimum_required(VERSION 3.23)
project(jute_editor)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

cmake_path(GET CMAKE_BINARY_DIR FILENAME REL_BINARY_DIR)
set(J_ENGINE_DLL_REL_DIR ../libjute-engine/${REL_BINARY_DIR})
set(J_ENGINE_H_REL_DIR ../libjute-engine)

link_directories(${J_ENGINE_DLL_REL_DIR} ${J_ENGINE_H_REL_DIR}/vendor/lib) # TODO: remove vendor from links?
include_directories(${J_ENGINE_H_REL_DIR} ${J_ENGINE_H_REL_DIR}/vendor) # TODO: remove vendor from includes?

add_executable(jute_editor jute/editor/core/editor.cpp)
target_link_libraries(jute_editor PRIVATE jute_engine PRIVATE spdlog) # TODO: remove spdlog
target_compile_definitions(jute_editor
        PUBLIC $<$<CONFIG:Debug>:LIBJUTE_ENGINE_SET_LOGGER_LEVEL_TRACE>
        PUBLIC $<$<CONFIG:Release>:LIBJUTE_ENGINE_SET_LOGGER_LEVEL_ERROR>)

add_custom_command(TARGET jute_editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_LIST_DIR}/${J_ENGINE_DLL_REL_DIR}/libjute_engine.dll"
        $<TARGET_FILE_DIR:jute_editor>)
