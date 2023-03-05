cmake_minimum_required(VERSION 3.23)
project(libjute-engine
        VERSION 0.1
        LANGUAGES CXX)

# set default build type
set(DEFAULT_BUILD_TYPE "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# find dependencies
find_package(spdlog REQUIRED HINTS "${CMAKE_CURRENT_LIST_DIR}/../.." PATH_SUFFIXES build cmake-build-release)

# generate configurable (.in) headers
configure_file(
        "${CMAKE_CURRENT_LIST_DIR}/cmake/libjute/engine/core/version.hpp.in"
        "${CMAKE_CURRENT_BINARY_DIR}/libjute/engine/core/version.hpp")

set(LIBJUTE_ENGINE_LOG_DIR "$ENV{LOCALAPPDATA}/Jute Engine/log" CACHE PATH "Log directory") # TODO: set for other platforms

# add target for Jute Engine shared library
add_library(libjute-engine SHARED)
add_library(jute-engine::libjute-engine ALIAS libjute-engine)
target_sources(libjute-engine
        PUBLIC FILE_SET public_headers TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES libjute/engine/core/defines.hpp libjute/engine/core/engine.hpp libjute/engine/core/logger.hpp
        PUBLIC FILE_SET public_generated_headers TYPE HEADERS BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR} FILES "${CMAKE_CURRENT_BINARY_DIR}/libjute/engine/core/version.hpp"
        INTERFACE FILE_SET interface_headers TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES libjute/engine/export.hpp # is it needed at all?
        PRIVATE libjute/engine/core/engine.cpp libjute/engine/core/logger.cpp)
target_link_libraries(libjute-engine PUBLIC spdlog::spdlog) # TODO: make spdlog private
target_compile_features(libjute-engine PUBLIC cxx_std_23)
target_compile_definitions(libjute-engine
        PRIVATE LIBJUTE_ENGINE_EXPORT
        PUBLIC LIBJUTE_ENGINE_LOG_DIR=\"${LIBJUTE_ENGINE_LOG_DIR}\"
        PUBLIC $<$<CONFIG:Debug>:LIBJUTE_ENGINE_SET_LOGGER_LEVEL_TRACE>
        PUBLIC $<$<CONFIG:Release>:LIBJUTE_ENGINE_SET_LOGGER_LEVEL_ERROR>)

# install
include(GNUInstallDirs)
install(TARGETS libjute-engine
        EXPORT libjute-engine
        FILE_SET public_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILE_SET public_generated_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILE_SET interface_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# cmake config
set(TARGETS_FILE "libjute-engine-targets.cmake")
set(EXPORT_DEST_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/libjute-engine")
set(CONFIG_PATH "${CMAKE_CURRENT_BINARY_DIR}/libjute-engine-config.cmake")
set(CONFIG_VERSION_PATH "${CMAKE_CURRENT_BINARY_DIR}/libjute-engine-config-version.cmake")

export(TARGETS libjute-engine
        NAMESPACE jute-engine::
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${TARGETS_FILE}")
install(EXPORT libjute-engine
        DESTINATION "${EXPORT_DEST_DIR}"
        NAMESPACE jute-engine::
        FILE "${TARGETS_FILE}")

include(CMakePackageConfigHelpers)
configure_package_config_file("${CMAKE_CURRENT_LIST_DIR}/cmake/libjute-engine-config.cmake.in" "${CONFIG_PATH}"
        INSTALL_DESTINATION ${EXPORT_DEST_DIR})
write_basic_package_version_file("${CONFIG_VERSION_PATH}" COMPATIBILITY SameMajorVersion)
install(FILES "${CONFIG_PATH}" "${CONFIG_VERSION_PATH}"
        DESTINATION "${EXPORT_DEST_DIR}")

include(cmake/libjute-engine-cpack.cmake)

# tests
option(LIBJUTE_ENGINE_BUILD_TESTS "Build tests" OFF)
if (LIBJUTE_ENGINE_BUILD_TESTS)
    enable_testing()
    add_executable(test-basic)
    target_sources(test-basic
            PUBLIC FILE_SET public_headers TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES tests/basic/main.hpp
            PRIVATE tests/basic/main.cpp)
    target_compile_features(test-basic PUBLIC cxx_std_23)
endif()
