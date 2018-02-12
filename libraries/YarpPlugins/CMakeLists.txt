# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

# Find YARP (common dependency for all devices).
find_package(YARP REQUIRED)

# Include YARP CMake modules (needless since YARP 2.3.70).
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})

# Utilities for creating YARP devices.
include(YarpPlugin)

# Common YARP includes for subdirectories (needless since YARP 2.3.70).
include_directories(${YARP_INCLUDE_DIRS})

# Make interface headers discoverable by subdirectories.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# YARP devices.
add_subdirectory(EcroPwmController)
add_subdirectory(EcroWheelController)
add_subdirectory(FakeMotorController)
add_subdirectory(LaserTowerOfDeathController)
add_subdirectory(RaspiOnePwmMotorController)
add_subdirectory(RaspiTwoPwmMotorController)
add_subdirectory(RobotClient)
add_subdirectory(RobotServer)

# Device interface target.
add_library(RobotInterfaces INTERFACE)

target_include_directories(RobotInterfaces INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                                     $<BUILD_INTERFACE:${YARP_INCLUDE_DIRS}> # get YARP_dev includes in 2.3.70+
                                                     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Install interface headers.
install(FILES IRobotManager.hpp
              DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Register export set.
install(TARGETS RobotInterfaces
        EXPORT ASROB_YARP_DEVICES)
