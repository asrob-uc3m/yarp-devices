# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(RaspiOnePwmMotorController
                    CATEGORY device
                    TYPE asrob::RaspiOnePwmMotorController
                    INCLUDE RaspiOnePwmMotorController.hpp
                    EXTRA_CONFIG WRAPPER=RobotServer
                    DEFAULT ${_rd_packaging_defaults}
                    DEPENDS UNIX)

if(NOT SKIP_RaspiOnePwmMotorController)

    yarp_add_plugin(RaspiOnePwmMotorController RaspiOnePwmMotorController.hpp
                                               RaspiOnePwmMotorController.cpp
                                               DeviceDriverImpl.cpp
                                               LogComponent.hpp
                                               LogComponent.cpp
                                               mailbox.h
                                               mailbox.c
                                               pwm.h
                                               pwm.c)

    target_link_libraries(RaspiOnePwmMotorController YARP::YARP_os
                                                     YARP::YARP_dev
                                                     ASROB::RobotInterfaces)

    yarp_install(TARGETS RaspiOnePwmMotorController
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
