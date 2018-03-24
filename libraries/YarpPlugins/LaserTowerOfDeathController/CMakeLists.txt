# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(LaserTowerOfDeathController
                    CATEGORY device
                    TYPE asrob::LaserTowerOfDeathController
                    INCLUDE LaserTowerOfDeathController.hpp
                    DEFAULT OFF)

if(NOT SKIP_LaserTowerOfDeathController)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    yarp_add_plugin(LaserTowerOfDeathController LaserTowerOfDeathController.hpp
                                                LaserTowerOfDeathController.cpp
                                                DeviceDriverImpl.cpp)

    add_dependencies(LaserTowerOfDeathController COLOR_DEBUG)

    target_link_libraries(LaserTowerOfDeathController YARP::YARP_OS
                                                      YARP::YARP_dev
                                                      serial)

    yarp_install(TARGETS LaserTowerOfDeathController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES LaserTowerOfDeathController.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
