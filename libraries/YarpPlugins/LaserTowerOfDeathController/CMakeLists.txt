# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

yarp_prepare_plugin(LaserTowerOfDeathController
                    CATEGORY device
                    TYPE asrob::LaserTowerOfDeathController
                    INCLUDE LaserTowerOfDeathController.hpp
                    DEFAULT OFF)

IF (NOT SKIP_LaserTowerOfDeathController)

    include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${YARP_INCLUDE_DIRS} )

    yarp_add_plugin(LaserTowerOfDeathController LaserTowerOfDeathController.cpp DeviceDriverImpl.cpp )

    TARGET_LINK_LIBRARIES(LaserTowerOfDeathController ${YARP_LIBRARIES} serial)

    yarp_install(TARGETS LaserTowerOfDeathController
                 COMPONENT runtime
                 LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES LaserTowerOfDeathController.ini
                 COMPONENT runtime
                 DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})

ENDIF (NOT SKIP_LaserTowerOfDeathController)
