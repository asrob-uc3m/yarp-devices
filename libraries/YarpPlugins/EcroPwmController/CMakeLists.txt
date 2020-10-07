# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

if(NOT LibSerial_FOUND AND (NOT DEFINED ENABLE_EcroPwmController OR ENABLE_EcroPwmController))
    message(WARNING "LibSerial package not found, disabling EcroPwmController device")
endif()

yarp_prepare_plugin(EcroPwmController
                    CATEGORY device
                    TYPE asrob::EcroPwmController
                    INCLUDE EcroPwmController.hpp
                    EXTRA_CONFIG WRAPPER=RobotServer
                    DEFAULT ${_rd_packaging_defaults}
                    DEPENDS LibSerial_FOUND)

if(NOT SKIP_EcroPwmController)

    if(NOT YARP_VERSION VERSION_GREATER_EQUAL 3.4)
        set(CMAKE_INCLUDE_CURRENT_DIR TRUE) # yarp plugin builder needs this
    endif()

    yarp_add_plugin(EcroPwmController EcroPwmController.hpp
                                      EcroPwmController.cpp
                                      DeviceDriverImpl.cpp)

    target_link_libraries(EcroPwmController YARP::YARP_os
                                            YARP::YARP_dev
                                            LibSerial::serial
                                            ROBOTICSLAB::ColorDebug
                                            RobotInterfaces)

    yarp_install(TARGETS EcroPwmController
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR}
                 YARP_INI DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

else()

    set(ENABLE_EcroPwmController OFF CACHE BOOL "Enable/disable EcroPwmController device" FORCE)

endif()
