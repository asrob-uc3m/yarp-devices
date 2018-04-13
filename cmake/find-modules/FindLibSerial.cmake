# Find the LibSerial library and headers.
#
# Sets the following variables:
#
# LibSerial_FOUND        - system has LibSerial
# LibSerial_VERSION      - LibSerial version
#
# ...and the following imported targets:
#
# LibSerial::serial      - the LibSerial library
#
# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1,
# see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

find_package(PkgConfig QUIET)

if(PKG_CONFIG_FOUND)
    pkg_check_modules(PC_LibSerial QUIET libserial)
endif()

if(NOT LibSerial_INCLUDE_DIR)
    find_path(LibSerial_INCLUDE_DIR NAMES SerialPort.h
                                          SerialStream.h
                                    PATHS "${PC_LibSerial_INCLUDEDIR}")
endif()

if(NOT LibSerial_LIBRARY)
    find_library(LibSerial_LIBRARY NAMES serial
                                   PATHS "${PC_LibSerial_LIBDIR}")
endif()

set(LibSerial_VERSION "${PC_LibSerial_VERSION}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibSerial FOUND_VAR LibSerial_FOUND
                                            REQUIRED_VARS LibSerial_INCLUDE_DIR LibSerial_LIBRARY
                                            VERSION_VAR PC_LibSerial_VERSION)

if(LibSerial_FOUND)
    add_library(LibSerial::serial UNKNOWN IMPORTED)

    set_target_properties(LibSerial::serial PROPERTIES IMPORTED_LOCATION "${LibSerial_LIBRARY}"
                                                       INTERFACE_INCLUDE_DIRECTORIES "${LibSerial_INCLUDE_DIR}")
endif()

mark_as_advanced(LibSerial_INCLUDE_DIR LibSerial_LIBRARY)
