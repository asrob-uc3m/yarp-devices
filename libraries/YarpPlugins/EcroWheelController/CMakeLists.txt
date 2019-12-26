# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

if(NOT LibSerial_FOUND AND (NOT DEFINED ENABLE_EcroWheelController OR ENABLE_EcroWheelController))
    message(WARNING "LibSerial package not found, disabling EcroWheelController device")
endif()

yarp_prepare_plugin(EcroWheelController
                    CATEGORY device
                    TYPE asrob::EcroWheelController
                    INCLUDE EcroWheelController.hpp
                    DEFAULT ${_rd_packaging_defaults}
                    DEPENDS LibSerial_FOUND)

if(NOT SKIP_EcroWheelController)

    if(YARP_VERSION VERSION_LESS 3.4)
        set(CMAKE_INCLUDE_CURRENT_DIR TRUE) # yarp plugin builder needs this
    endif()

    yarp_add_plugin(EcroWheelController EcroWheelController.hpp
                                        EcroWheelController.cpp
                                        DeviceDriverImpl.cpp)

    target_link_libraries(EcroWheelController YARP::YARP_OS
                                              YARP::YARP_dev
                                              LibSerial::serial
                                              ROBOTICSLAB::ColorDebug
                                              RobotInterfaces)

    yarp_install(TARGETS EcroWheelController
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

else()

    set(ENABLE_EcroWheelController OFF CACHE BOOL "Enable/disable EcroWheelController device" FORCE)

endif()
