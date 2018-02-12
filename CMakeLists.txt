# Copyright: Universidad Carlos III de Madrid (C) 2013;
# Authors: Juan G. Victores & Raúl de Santos Rico
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)

project(ASROB_YARP_DEVICES)

# Safety check against missing dummy library for system-available COLOR_DEBUG.
# Remove if cmake_minimum_required() above is set to 3.0 or later.
if(POLICY CMP0046)
    cmake_policy(SET CMP0046 NEW)
endif()

# Force building shared libraries and YARP DL modules.
set(BUILD_SHARED_LIBS TRUE CACHE INTERNAL "hide this!")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -frtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")

# Hack to compile against YARP 2.3.68.
# https://github.com/asrob-uc3m/yarp-devices/issues/89
add_definitions(-DYARP_NO_DEPRECATED_WARNINGS=ON)

# Add suffix for debug libraries.
if(MSVC)
    message(STATUS "Running on windows")
    set(CMAKE_DEBUG_POSTFIX "d")
endif()

# Let the user specify a configuration (only single-config generators).
if(NOT CMAKE_CONFIGURATION_TYPES)
    # Possible values.
    set(_configurations Debug Release MinSizeRel RelWithDebInfo)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${_configurations})

    foreach(_conf ${_configurations})
        set(_conf_string "${_conf_string} ${_conf}")
    endforeach()

    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING
                 "Choose the type of build, options are:${_conf_string}")

    if(NOT CMAKE_BUILD_TYPE)
        # Encourage the user to specify build type.
        message(STATUS "Setting build type to 'Release' as none was specified.")
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE Release)
    endif()
endif()

# Pick up our CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Bootstrap YCM. Stick to v0.2.2 because of:
# https://github.com/robotology/ycm/issues/118
# ...and to keep YCM itself compatible with cmake_minimum_required().
set(YCM_TAG v0.2.2)
include(YCMBootstrap)

# Standard installation directories.
include(GNUInstallDirs)

# Control where libraries and executables are placed during the build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

# Enabling coverage.
option(ENABLE_coverage "Choose if you want to enable coverage collection" OFF)

if(ENABLE_coverage)
    # List supported compilers.
    if(CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    endif()
endif()

# Superbuild phase - include color-debug.
include(FindOrBuildPackage)
find_or_build_package(COLOR_DEBUG)

# find_or_build_package() doesn't bring into scope COLOR_DEBUG_INCLUDE_DIRS
# nor other config variables. If a system copy is found, we have to call the
# find_package() command and proceed as usual.
if(USE_SYSTEM_COLOR_DEBUG)
    find_package(COLOR_DEBUG REQUIRED)
    include_directories(${COLOR_DEBUG_INCLUDE_DIRS})
endif()

# Create targets if specific requirements are satisfied.
include(CMakeDependentOption)

# Add main contents.
add_subdirectory(share)
add_subdirectory(libraries)
#add_subdirectory(programs)
#add_subdirectory(tests)

# Store the package in the user registry.
export(PACKAGE ASROB_YARP_DEVICES)

# CMake installation path.
if(WIN32)
    set(_cmake_destination cmake)
else()
    set(_cmake_destination ${CMAKE_INSTALL_LIBDIR}/cmake/ASROB_YARP_DEVICES)
endif()

# Create and install config files.
include(CMakePackageConfigHelpers)

# <pkg>Config.cmake (build tree).
configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/template/ASROB_YARP_DEVICESConfig.cmake.in
                              ${CMAKE_BINARY_DIR}/ASROB_YARP_DEVICESConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_BINARY_DIR}
                              INSTALL_PREFIX ${CMAKE_BINARY_DIR}
                              NO_SET_AND_CHECK_MACRO
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

# <pkg>Config.cmake (install tree).
configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/template/ASROB_YARP_DEVICESConfig.cmake.in
                              ${CMAKE_BINARY_DIR}/ASROB_YARP_DEVICESConfig.cmake.install
                              INSTALL_DESTINATION ${_cmake_destination}
                              NO_SET_AND_CHECK_MACRO
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

# Install <pkg>Config.cmake.
install(FILES ${CMAKE_BINARY_DIR}/ASROB_YARP_DEVICESConfig.cmake.install
        RENAME ASROB_YARP_DEVICESConfig.cmake
        DESTINATION ${_cmake_destination})

# Export targets (build tree).
export(TARGETS RobotInterfaces
       NAMESPACE ASROB::
       FILE ASROB_YARP_DEVICESTargets.cmake)

# Export targets (install tree).
install(EXPORT ASROB_YARP_DEVICES
        DESTINATION ${_cmake_destination}
        NAMESPACE ASROB::
        FILE ASROB_YARP_DEVICESTargets.cmake)

# Configure and create uninstall target.
include(AddUninstallTarget)
