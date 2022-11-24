# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(EcroWheelController
                    CATEGORY device
                    TYPE asrob::EcroWheelController
                    INCLUDE EcroWheelController.hpp
                    EXTRA_CONFIG WRAPPER=RobotServer
                    DEFAULT ${_rd_packaging_defaults})

if(NOT SKIP_EcroWheelController)

    yarp_add_plugin(EcroWheelController EcroWheelController.hpp
                                        EcroWheelController.cpp
                                        DeviceDriverImpl.cpp
                                        LogComponent.hpp
                                        LogComponent.cpp)

    target_link_libraries(EcroWheelController YARP::YARP_os
                                              YARP::YARP_dev
                                              ASROB::RobotInterfaces)

    yarp_install(TARGETS EcroWheelController
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
