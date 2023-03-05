cmake_minimum_required(VERSION 3.23)
project(jute-editor
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
cmake_path(GET CMAKE_CURRENT_BINARY_DIR FILENAME REL_BINARY_DIR)
find_package(libjute-engine REQUIRED HINTS "${CMAKE_CURRENT_LIST_DIR}/.." PATH_SUFFIXES "${REL_BINARY_DIR}" build)

# generate configurable (.in) headers
configure_file(
        "${CMAKE_CURRENT_LIST_DIR}/cmake/jute/editor/core/version.hpp.in"
        "${CMAKE_CURRENT_BINARY_DIR}/jute/editor/core/version.hpp")

# add target for Jute Editor executable
add_executable(jute-editor)
add_executable(jute-editor::jute-editor ALIAS jute-editor)
target_sources(jute-editor
        PUBLIC FILE_SET public_headers TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}"
        PUBLIC FILE_SET public_generated_headers TYPE HEADERS BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR} FILES "${CMAKE_CURRENT_BINARY_DIR}/jute/editor/core/version.hpp"
        INTERFACE FILE_SET interface_headers TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}"
        PRIVATE FILE_SET private_headers TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_LIST_DIR}" FILES jute/editor/core/editor.hpp # or public?
        PRIVATE jute/editor/core/editor.cpp)
target_link_libraries(jute-editor PRIVATE jute-engine::libjute-engine)
target_compile_features(jute-editor PUBLIC cxx_std_23)
target_compile_definitions(jute-editor
        PUBLIC $<$<CONFIG:Debug>:LIBJUTE_ENGINE_SET_LOGGER_LEVEL_TRACE>
        PUBLIC $<$<CONFIG:Release>:LIBJUTE_ENGINE_SET_LOGGER_LEVEL_ERROR>)

# copy needed dlls TODO: only do it on Windows
add_custom_command(TARGET jute-editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:jute-engine::libjute-engine>"
        "$<TARGET_FILE_DIR:jute-editor>")

# install
include(GNUInstallDirs)
install(TARGETS jute-editor
        EXPORT jute-editor
        FILE_SET public_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILE_SET public_generated_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILE_SET interface_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES "$<TARGET_FILE:jute-engine::libjute-engine>" DESTINATION ${CMAKE_INSTALL_BINDIR})

# cmake config
set(TARGETS_FILE "jute-editor-targets.cmake")
set(EXPORT_DEST_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/jute-editor")
set(CONFIG_PATH "${CMAKE_CURRENT_BINARY_DIR}/jute-editor-config.cmake")
set(CONFIG_VERSION_PATH "${CMAKE_CURRENT_BINARY_DIR}/jute-editor-config-version.cmake")

export(TARGETS jute-editor
        NAMESPACE jute-editor::
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${TARGETS_FILE}")
install(EXPORT jute-editor
        DESTINATION "${EXPORT_DEST_DIR}"
        NAMESPACE jute-editor::
        FILE "${TARGETS_FILE}")

include(CMakePackageConfigHelpers)
configure_package_config_file("${CMAKE_CURRENT_LIST_DIR}/cmake/jute-editor-config.cmake.in" "${CONFIG_PATH}"
        INSTALL_DESTINATION ${EXPORT_DEST_DIR})
write_basic_package_version_file("${CONFIG_VERSION_PATH}" COMPATIBILITY SameMajorVersion)
install(FILES "${CONFIG_PATH}" "${CONFIG_VERSION_PATH}"
        DESTINATION "${EXPORT_DEST_DIR}")

include(cmake/jute-editor-cpack.cmake)
