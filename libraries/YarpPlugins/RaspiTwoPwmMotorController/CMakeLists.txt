# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(RaspiTwoPwmMotorController
                    CATEGORY device
                    TYPE asrob::RaspiTwoPwmMotorController
                    INCLUDE RaspiTwoPwmMotorController.hpp
                    DEFAULT OFF)

if(NOT SKIP_RaspiTwoPwmMotorController)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    yarp_add_plugin(RaspiTwoPwmMotorController RaspiTwoPwmMotorController.hpp
                                               RaspiTwoPwmMotorController.cpp
                                               DeviceDriverImpl.cpp)

    add_dependencies(RaspiTwoPwmMotorController COLOR_DEBUG)

    target_link_libraries(RaspiTwoPwmMotorController YARP::YARP_OS
                                                     YARP::YARP_dev
                                                     RobotInterfaces)

    yarp_install(TARGETS RaspiTwoPwmMotorController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES RaspiTwoPwmMotorController.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
