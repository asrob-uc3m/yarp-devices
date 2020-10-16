cmake_minimum_required(VERSION 2.8.0)

# Start a project.
project(exampleRobotClient)

find_package(YARP REQUIRED COMPONENTS os dev sig)
find_package(ASROB_YARP_DEVICES REQUIRED)

# Set up our main executables.

add_executable(exampleRobotClient exampleRobotClient.cpp)

target_link_libraries(exampleRobotClient YARP::YARP_OS
                                         YARP::YARP_init
                                         YARP::YARP_dev)

include(GNUInstallDirs)

install(TARGETS exampleRobotClient
        DESTINATION ${CMAKE_INSTALL_BINDIR})
