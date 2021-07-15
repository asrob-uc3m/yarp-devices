# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

if(NOT LibSerial_FOUND AND (NOT DEFINED ENABLE_LaserTowerOfDeathController OR ENABLE_LaserTowerOfDeathController))
    message(WARNING "LibSerial package not found, disabling LaserTowerOfDeathController device")
endif()

yarp_prepare_plugin(LaserTowerOfDeathController
                    CATEGORY device
                    TYPE asrob::LaserTowerOfDeathController
                    INCLUDE LaserTowerOfDeathController.hpp
                    EXTRA_CONFIG WRAPPER=RobotServer
                    DEFAULT ${_rd_packaging_defaults}
                    DEPENDS LibSerial_FOUND)

if(NOT SKIP_LaserTowerOfDeathController)

    yarp_add_plugin(LaserTowerOfDeathController LaserTowerOfDeathController.hpp
                                                LaserTowerOfDeathController.cpp
                                                DeviceDriverImpl.cpp
                                                LogComponent.hpp
                                                LogComponent.cpp)

    target_link_libraries(LaserTowerOfDeathController YARP::YARP_os
                                                      YARP::YARP_dev
                                                      LibSerial::serial
                                                      ASROB::RobotInterfaces)

    yarp_install(TARGETS LaserTowerOfDeathController
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

else()

    set(ENABLE_LaserTowerOfDeathController OFF CACHE BOOL "Enable/disable LaserTowerOfDeathController device" FORCE)

endif()
