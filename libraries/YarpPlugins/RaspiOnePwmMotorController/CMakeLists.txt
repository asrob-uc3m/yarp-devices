# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(RaspiOnePwmMotorController
                    CATEGORY device
                    TYPE asrob::RaspiOnePwmMotorController
                    INCLUDE RaspiOnePwmMotorController.hpp
                    DEFAULT OFF)

IF (NOT SKIP_RaspiOnePwmMotorController)

    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")  # sorry

    include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${YARP_INCLUDE_DIRS} )

    yarp_add_plugin(RaspiOnePwmMotorController RaspiOnePwmMotorController.cpp DeviceDriverImpl.cpp pwm.cpp)

    TARGET_LINK_LIBRARIES(RaspiOnePwmMotorController ${YARP_LIBRARIES})

    yarp_install(TARGETS RaspiOnePwmMotorController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES RaspiOnePwmMotorController.ini
                 COMPONENT runtime
                 DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

ENDIF (NOT SKIP_RaspiOnePwmMotorController)
