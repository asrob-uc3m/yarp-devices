# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

if(NOT wiringPi_FOUND AND (NOT DEFINED ENABLE_RaspiTwoPwmMotorController OR ENABLE_RaspiTwoPwmMotorController))
    message(WARNING "wiringPi package not found, disabling RaspiTwoPwmMotorController device")
endif()

yarp_prepare_plugin(RaspiTwoPwmMotorController
                    CATEGORY device
                    TYPE asrob::RaspiTwoPwmMotorController
                    INCLUDE RaspiTwoPwmMotorController.hpp
                    EXTRA_CONFIG WRAPPER=RobotServer
                    DEFAULT ${_rd_packaging_defaults}
                    DEPENDS "UNIX;wiringPi_FOUND")

if(NOT SKIP_RaspiTwoPwmMotorController)

    yarp_add_plugin(RaspiTwoPwmMotorController RaspiTwoPwmMotorController.hpp
                                               RaspiTwoPwmMotorController.cpp
                                               DeviceDriverImpl.cpp)

    target_link_libraries(RaspiTwoPwmMotorController YARP::YARP_os
                                                     YARP::YARP_dev
                                                     wiringPi::wiringPi
                                                     ASROB::RobotInterfaces)

    yarp_install(TARGETS RaspiTwoPwmMotorController
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

else()

    set(ENABLE_RaspiTwoPwmMotorController OFF CACHE BOOL "Enable/disable RaspiTwoPwmMotorController device" FORCE)

endif()
