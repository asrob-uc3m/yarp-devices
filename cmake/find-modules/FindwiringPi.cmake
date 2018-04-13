# Find the wiringPi library and headers.
#
# Sets the following variables:
#
# wiringPi_FOUND        - system has wiringPi
#
# ...and the following imported targets:
#
# wiringPi::wiringPi    - the wiringPi library
# wiringPi::wiringPiDev - the wiringPi development library
#
# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1,
# see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

if(NOT wiringPi_INCLUDE_DIR)
    find_path(wiringPi_INCLUDE_DIR wiringPi.h)
endif()

if(NOT wiringPi_LIBRARY)
    find_library(wiringPi_LIBRARY wiringPi)
endif()

if(NOT wiringPi_LIBRARY_DEV)
    find_library(wiringPi_LIBRARY_DEV wiringPiDev)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(wiringPi FOUND_VAR wiringPi_FOUND
                                           REQUIRED_VARS wiringPi_INCLUDE_DIR wiringPi_LIBRARY wiringPi_LIBRARY_DEV)

if(wiringPi_FOUND)
    add_library(wiringPi::wiringPi UNKNOWN IMPORTED)
    add_library(wiringPi::wiringPiDev UNKNOWN IMPORTED)

    set_target_properties(wiringPi::wiringPi PROPERTIES IMPORTED_LOCATION "${wiringPi_LIBRARY}"
                                                        INTERFACE_INCLUDE_DIRECTORIES "${wiringPi_INCLUDE_DIR}")

    set_target_properties(wiringPi::wiringPiDev PROPERTIES IMPORTED_LOCATION "${wiringPi_LIBRARY_DEV}"
                                                           INTERFACE_INCLUDE_DIRECTORIES "${wiringPi_INCLUDE_DIR}")
endif()

mark_as_advanced(wiringPi_INCLUDE_DIR wiringPi_LIBRARY wiringPi_LIBRARY_DEV)
