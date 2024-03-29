# Copyright: Universidad Carlos III de Madrid (C) 2013;
# Authors: Juan G. Victores & Raúl de Santos Rico
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.12)

# Honor wiringPi_ROOT env variable in FindwiringPi.cmake (CMake 3.12).
if(POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

project(ASROB_YARP_DEVICES)

# Add suffix for debug libraries.
if(MSVC)
    message(STATUS "Running on Windows")
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
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake
                              ${CMAKE_SOURCE_DIR}/cmake/find-modules)

# Hard dependencies.
find_package(YCM 0.11 REQUIRED)
find_package(YARP 3.5 REQUIRED COMPONENTS os dev)

# Soft dependencies.
find_package(wiringPi QUIET)
find_package(SWIG 3.0.12 QUIET)
find_package(Doxygen QUIET)

# Always build YARP devices as MODULE libraries.
set(YARP_FORCE_DYNAMIC_PLUGINS TRUE CACHE INTERNAL "Force dynamic plugins")

# Configure installation paths for YARP resources.
yarp_configure_external_installation(asrob-yarp-devices WITH_PLUGINS)

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

# Disable specific options for RD packaging.
option(RD_PACKAGING "Configure project for RobotDevastation CPack" OFF)
mark_as_advanced(RD_PACKAGING)

if(RD_PACKAGING)
    set(_rd_packaging_defaults OFF)
else()
    set(_rd_packaging_defaults ON)
endif()

# Create targets if specific requirements are satisfied.
include(CMakeDependentOption)

# Add main contents.
add_subdirectory(libraries)
#add_subdirectory(tests)
add_subdirectory(share)
add_subdirectory(bindings)
add_subdirectory(doc)
add_subdirectory(examples/cpp)

# Store the package in the user registry.
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)

if(_rd_packaging_defaults)
    # Create and install config files.
    include(InstallBasicPackageFiles)

    install_basic_package_files(ASROB_YARP_DEVICES
                                VERSION 0.1.0
                                COMPATIBILITY AnyNewerVersion
                                NO_SET_AND_CHECK_MACRO
                                NO_CHECK_REQUIRED_COMPONENTS_MACRO
                                NAMESPACE ASROB::)
endif()

# Configure and create uninstall target.
include(AddUninstallTarget)
