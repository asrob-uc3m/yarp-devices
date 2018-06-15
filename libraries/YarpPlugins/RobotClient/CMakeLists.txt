# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(RobotClient
                    CATEGORY device
                    TYPE asrob::RobotClient
                    INCLUDE RobotClient.hpp
                    DEFAULT ON)

if(NOT SKIP_RobotClient)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    yarp_add_plugin(RobotClient RobotClient.hpp
                                RobotClient.cpp
                                DeviceDriverImpl.cpp)

    target_link_libraries(RobotClient YARP::YARP_OS
                                      YARP::YARP_dev
                                      ROBOTICSLAB::ColorDebug
                                      RobotInterfaces)

    yarp_install(TARGETS RobotClient
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES RobotClient.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
