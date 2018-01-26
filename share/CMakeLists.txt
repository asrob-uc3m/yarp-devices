# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

find_package(YARP REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
include(YarpInstallationHelpers)
yarp_configure_external_installation(asrob-yarp-devices)

yarp_install(FILES ymanager.ini
             DESTINATION ${ASROB-YARP-DEVICES_DATA_INSTALL_DIR})

### Go through single applications

