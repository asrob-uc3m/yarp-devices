# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(RobotServer
                    CATEGORY device
                    TYPE asrob::RobotServer
                    INCLUDE RobotServer.hpp
                    EXTRA_CONFIG WRAPPER=RobotServer
                    DEFAULT ${_rd_packaging_defaults})

if(NOT SKIP_RobotServer)

    yarp_add_plugin(RobotServer RobotServer.hpp
                                RobotServer.cpp
                                DeviceDriverImpl.cpp
                                LogComponent.hpp
                                LogComponent.cpp)

    target_link_libraries(RobotServer YARP::YARP_os
                                      YARP::YARP_dev
                                      ASROB::RobotInterfaces)

    yarp_install(TARGETS RobotServer
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
