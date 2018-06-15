# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(FakeMotorController
                    CATEGORY device
                    TYPE asrob::FakeMotorController
                    INCLUDE FakeMotorController.hpp
                    DEFAULT ON)

if(NOT SKIP_FakeMotorController)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    yarp_add_plugin(FakeMotorController FakeMotorController.hpp
                                        FakeMotorController.cpp
                                        DeviceDriverImpl.cpp)

    target_link_libraries(FakeMotorController YARP::YARP_OS
                                              YARP::YARP_dev
                                              ROBOTICSLAB::ColorDebug
                                              RobotInterfaces)

    yarp_install(TARGETS FakeMotorController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES FakeMotorController.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
