# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

find_package(LibSerial 0.6 QUIET)

if(NOT LibSerial_FOUND AND (NOT DEFINED ENABLE_LaserTowerOfDeathController OR ENABLE_LaserTowerOfDeathController))
    message(WARNING "LibSerial package not found, disabling LaserTowerOfDeathController device")
endif()

yarp_prepare_plugin(LaserTowerOfDeathController
                    CATEGORY device
                    TYPE asrob::LaserTowerOfDeathController
                    INCLUDE LaserTowerOfDeathController.hpp
                    DEFAULT ON
                    DEPENDS LibSerial_FOUND)

if(NOT SKIP_LaserTowerOfDeathController)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    yarp_add_plugin(LaserTowerOfDeathController LaserTowerOfDeathController.hpp
                                                LaserTowerOfDeathController.cpp
                                                DeviceDriverImpl.cpp)

    add_dependencies(LaserTowerOfDeathController COLOR_DEBUG)

    target_link_libraries(LaserTowerOfDeathController YARP::YARP_OS
                                                      YARP::YARP_dev
                                                      LibSerial::serial
                                                      RobotInterfaces)

    yarp_install(TARGETS LaserTowerOfDeathController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES LaserTowerOfDeathController.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

else()

    set(ENABLE_LaserTowerOfDeathController OFF CACHE BOOL "Enable/disable LaserTowerOfDeathController device" FORCE)

endif()
