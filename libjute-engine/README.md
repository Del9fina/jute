# Jute Engine

This is the engine itself, the output is a shared library.

### Building and installing libjute-engine

Build and install with CMake. CPack supported.

### Including libjute-engine with CMake

```
find_package(libjute-engine)
target_link_libraries(your-target jute-engine::libjute-engine)
```

If on Windows, consider the following command:

```
add_custom_command(TARGET your-target POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:jute-engine::libjute-engine>"
        "$<TARGET_FILE_DIR:your-target>")
```

### Dependencies

- [spdlog](https://github.com/gabime/spdlog) (v1.x)