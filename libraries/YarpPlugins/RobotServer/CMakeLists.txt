# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(RobotServer
                    CATEGORY device
                    TYPE asrob::RobotServer
                    INCLUDE RobotServer.hpp
                    DEFAULT ${_rd_packaging_defaults})

if(NOT SKIP_RobotServer)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    yarp_add_plugin(RobotServer RobotServer.hpp
                                RobotServer.cpp
                                DeviceDriverImpl.cpp)

    target_link_libraries(RobotServer YARP::YARP_OS
                                      YARP::YARP_dev
                                      ROBOTICSLAB::ColorDebug
                                      RobotInterfaces)

    yarp_install(TARGETS RobotServer
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES RobotServer.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
