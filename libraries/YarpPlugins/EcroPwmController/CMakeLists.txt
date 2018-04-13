# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(EcroPwmController
                    CATEGORY device
                    TYPE asrob::EcroPwmController
                    INCLUDE EcroPwmController.hpp
                    DEFAULT ON)

if(NOT SKIP_EcroPwmController)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    yarp_add_plugin(EcroPwmController EcroPwmController.hpp
                                      EcroPwmController.cpp
                                      DeviceDriverImpl.cpp)

    add_dependencies(EcroPwmController COLOR_DEBUG)

    target_link_libraries(EcroPwmController YARP::YARP_OS
                                            YARP::YARP_dev
                                            serial)

    yarp_install(TARGETS EcroPwmController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES EcroPwmController.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
