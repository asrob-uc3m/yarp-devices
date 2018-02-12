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

# Install interface headers.
install(FILES IRobotManager.hpp
              DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export variables to the global scope.
set_property(GLOBAL APPEND PROPERTY ASROB_YARP_DEVICES_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})
