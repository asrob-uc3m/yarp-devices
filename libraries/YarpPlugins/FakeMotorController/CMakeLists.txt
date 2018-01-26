# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(FakeMotorController
                    CATEGORY device
                    TYPE asrob::FakeMotorController
                    INCLUDE FakeMotorController.hpp
                    DEFAULT ON)

IF (NOT SKIP_FakeMotorController)

    include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${YARP_INCLUDE_DIRS} )

    yarp_add_plugin(FakeMotorController FakeMotorController.cpp DeviceDriverImpl.cpp )

    TARGET_LINK_LIBRARIES(FakeMotorController ${YARP_LIBRARIES})

    yarp_install(TARGETS FakeMotorController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES FakeMotorController.ini
                 COMPONENT runtime
                 DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

ENDIF (NOT SKIP_FakeMotorController)
