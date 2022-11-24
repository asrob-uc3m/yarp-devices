# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(EcroPwmController
                    CATEGORY device
                    TYPE asrob::EcroPwmController
                    INCLUDE EcroPwmController.hpp
                    EXTRA_CONFIG WRAPPER=RobotServer
                    DEFAULT ${_rd_packaging_defaults})

if(NOT SKIP_EcroPwmController)

    yarp_add_plugin(EcroPwmController EcroPwmController.hpp
                                      EcroPwmController.cpp
                                      DeviceDriverImpl.cpp
                                      LogComponent.hpp
                                      LogComponent.cpp)

    target_link_libraries(EcroPwmController YARP::YARP_os
                                            YARP::YARP_dev
                                            ASROB::RobotInterfaces)

    yarp_install(TARGETS EcroPwmController
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
