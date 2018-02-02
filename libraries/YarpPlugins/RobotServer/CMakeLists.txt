# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(RobotServer
                    CATEGORY device
                    TYPE asrob::RobotServer
                    INCLUDE RobotServer.hpp
                    DEFAULT ON)

IF (NOT SKIP_RobotServer)

    include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

    yarp_add_plugin(RobotServer RobotServer.hpp RobotServer.cpp DeviceDriverImpl.cpp )

    TARGET_LINK_LIBRARIES(RobotServer ${YARP_LIBRARIES})

    yarp_install(TARGETS RobotServer
                 COMPONENT runtime
                 LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES RobotServer.ini
                 COMPONENT runtime
                 DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})


ENDIF (NOT SKIP_RobotServer)
