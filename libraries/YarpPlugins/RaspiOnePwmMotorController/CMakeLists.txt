# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(RaspiOnePwmMotorController
                    CATEGORY device
                    TYPE asrob::RaspiOnePwmMotorController
                    INCLUDE RaspiOnePwmMotorController.hpp
                    DEFAULT ${_rd_packaging_defaults}
                    DEPENDS UNIX)

if(NOT SKIP_RaspiOnePwmMotorController)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    yarp_add_plugin(RaspiOnePwmMotorController RaspiOnePwmMotorController.hpp
                                               RaspiOnePwmMotorController.cpp
                                               DeviceDriverImpl.cpp
                                               mailbox.h
                                               mailbox.c
                                               pwm.h
                                               pwm.c)

    target_link_libraries(RaspiOnePwmMotorController YARP::YARP_OS
                                                     YARP::YARP_dev
                                                     ROBOTICSLAB::ColorDebug
                                                     RobotInterfaces)

    yarp_install(TARGETS RaspiOnePwmMotorController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES RaspiOnePwmMotorController.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
