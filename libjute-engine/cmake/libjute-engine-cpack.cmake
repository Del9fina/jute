set(CPACK_GENERATOR "TGZ;ZIP;NSIS" CACHE STRING "Semicolon separated list of generators")

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
set(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR}" "${PROJECT_NAME}" ALL .)

set(CPACK_PROJECT_URL "https://github.com/Del9fina/jute")
set(CPACK_PACKAGE_VENDOR "Del9fina")
set(CPACK_PACKAGE_CONTACT "Del9fina")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "C++ 3D game engine")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
if (PROJECT_VERSION_PATCH)
    set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
    set(CPACK_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION}.${PROJECT_VERSION_PATCH})
endif()
if (PROJECT_VERSION_TWEAK)
    set(CPACK_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION}.${PROJECT_VERSION_TWEAK})
endif()
set(CPACK_PACKAGE_RELOCATABLE ON CACHE BOOL "Build relocatable package")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "libjute-engine")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "libjute-engine-${CPACK_PACKAGE_VERSION}")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_LIST_DIR}/../../LICENSE")

set(CPACK_NSIS_DISPLAY_NAME "Jute Engine Library")
set(CPACK_NSIS_PACKAGE_NAME "libjute-engine-${CPACK_PACKAGE_VERSION}")

set(CPACK_RPM_PACKAGE_LICENSE "GNU")
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_DEBIAN_PACKAGE_SECTION "libs")
set(CPACK_RPM_PACKAGE_URL ${CPACK_PROJECT_URL})
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${CPACK_PROJECT_URL})
set(CPACK_RPM_PACKAGE_DESCRIPTION "C++ 3D game engine")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "C++ 3D game engine")

if (CPACK_PACKAGE_NAME)
    set(CPACK_RPM_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
    set(CPACK_DEBIAN_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
else()
    set(CPACK_RPM_FILE_NAME "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
    set(CPACK_DEBIAN_FILE_NAME "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
    set(CPACK_RPM_PACKAGE_NAME "${PROJECT_NAME}")
    set(CPACK_DEBIAN_PACKAGE_NAME "${PROJECT_NAME}")
endif()

if (CPACK_RPM_PACKAGE_RELEASE)
    set(CPACK_RPM_FILE_NAME "${CPACK_RPM_FILE_NAME}-${CPACK_RPM_PACKAGE_RELEASE}")
endif()
if (CPACK_DEBIAN_PACKAGE_RELEASE)
    set(CPACK_DEBIAN_FILE_NAME "${CPACK_DEBIAN_FILE_NAME}-${CPACK_DEBIAN_PACKAGE_RELEASE}")
endif()

if (CPACK_RPM_PACKAGE_ARCHITECTURE)
    set(CPACK_RPM_FILE_NAME "${CPACK_RPM_FILE_NAME}.${CPACK_RPM_PACKAGE_ARCHITECTURE}")
endif()
if (CPACK_DEBIAN_PACKAGE_ARCHITECTURE)
    set(CPACK_DEBIAN_FILE_NAME "${CPACK_DEBIAN_FILE_NAME}.${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
endif()
set(CPACK_RPM_FILE_NAME "${CPACK_RPM_FILE_NAME}.rpm")
set(CPACK_DEBIAN_FILE_NAME "${CPACK_DEBIAN_FILE_NAME}.deb")

include(CPack)
