# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

if(_rd_packaging_defaults)
    yarp_install(FILES ymanager.ini
                 DESTINATION ${ASROB-YARP-DEVICES_DATA_INSTALL_DIR})
endif()

### Go through single applications
