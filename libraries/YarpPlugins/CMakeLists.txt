# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

if(YARP_VERSION_SHORT VERSION_LESS 2.3.70)
    include_directories(${YARP_INCLUDE_DIRS})
endif()

# Device interface target.
add_library(RobotInterfaces INTERFACE)

# Configure usage requirements.
target_include_directories(RobotInterfaces INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                                                     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Install interface headers.
install(FILES IRobotManager.hpp
              DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Register export set.
install(TARGETS RobotInterfaces
        EXPORT ASROB_YARP_DEVICES)

# Always build YARP devices as MODULE libraries.
set(YARP_FORCE_DYNAMIC_PLUGINS TRUE CACHE INTERNAL "Force dynamic plugins")

# YARP devices.
add_subdirectory(EcroPwmController)
add_subdirectory(EcroWheelController)
add_subdirectory(FakeMotorController)
add_subdirectory(LaserTowerOfDeathController)
add_subdirectory(RaspiOnePwmMotorController)
add_subdirectory(RaspiTwoPwmMotorController)
add_subdirectory(RobotClient)
add_subdirectory(RobotServer)
