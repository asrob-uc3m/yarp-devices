# Authors: see AUTHORS.md at project root.
# CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
# URL: https://github.com/asrob-uc3m/yarp-devices

find_package(ARSDK QUIET)

if(NOT ARSDK_FOUND AND (NOT DEFINED ENABLE_JumpingSumo OR ENABLE_JumpingSumo))
    message(WARNING "ARSDK package not found, disabling JumpingSumo device")
endif()

yarp_prepare_plugin(JumpingSumo
                    CATEGORY device
                    TYPE asrob::JumpingSumo
                    INCLUDE JumpingSumo.hpp
                    DEFAULT ON
                    DEPENDS ARSDK_FOUND)

if(NOT SKIP_JumpingSumo)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                        ${ARSDK_INCLUDE_DIRS})

    link_directories(${ARSDK_LINK_DIRS})

    yarp_add_plugin(JumpingSumo JumpingSumo.hpp
                                JumpingSumo.cpp
                                DeviceDriverImpl.cpp
                                IRobotManagerImpl.cpp)

    add_dependencies(JumpingSumo COLOR_DEBUG)

    target_link_libraries(JumpingSumo YARP::YARP_OS
                                      YARP::YARP_dev
                                      YARP::YARP_sig
                                      ${ARSDK_LIBRARIES}
                                      RobotInterfaces)

    yarp_install(TARGETS JumpingSumo
                 COMPONENT runtime
                 LIBRARY DESTINATION ${ASROB-YARP-DEVICES_DYNAMIC_PLUGINS_INSTALL_DIR}
                 ARCHIVE DESTINATION ${ASROB-YARP-DEVICES_STATIC_PLUGINS_INSTALL_DIR})

    yarp_install(FILES JumpingSumo.ini
                 COMPONENT runtime
                 DESTINATION ${ASROB-YARP-DEVICES_PLUGIN_MANIFESTS_INSTALL_DIR})

else()

    set(ENABLE_JumpingSumo OFF CACHE BOOL "Enable/disable JumpingSumo device" FORCE)

endif()
