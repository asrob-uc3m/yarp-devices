# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(EcroWheelController
                    CATEGORY device
                    TYPE asrob::EcroWheelController
                    INCLUDE EcroWheelController.hpp
                    DEFAULT OFF)

if(NOT SKIP_EcroWheelController)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})

    yarp_add_plugin(EcroWheelController EcroWheelController.hpp
                                        EcroWheelController.cpp
                                        DeviceDriverImpl.cpp)

    add_dependencies(EcroWheelController COLOR_DEBUG)

    target_link_libraries(EcroWheelController YARP::YARP_OS
                                              YARP::YARP_dev
                                              serial)

    yarp_install(TARGETS EcroWheelController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES EcroWheelController.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

endif()
