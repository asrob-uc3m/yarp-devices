# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(EcroWheelController
                    CATEGORY device
                    TYPE asrob::EcroWheelController
                    INCLUDE EcroWheelController.hpp
                    DEFAULT OFF)

IF (NOT SKIP_EcroWheelController)

    include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${YARP_INCLUDE_DIRS} )

    yarp_add_plugin(EcroWheelController EcroWheelController.cpp DeviceDriverImpl.cpp )

    TARGET_LINK_LIBRARIES(EcroWheelController ${YARP_LIBRARIES} serial)

    yarp_install(TARGETS EcroWheelController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES EcroWheelController.ini
                 COMPONENT runtime
                 DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

ENDIF (NOT SKIP_EcroWheelController)
