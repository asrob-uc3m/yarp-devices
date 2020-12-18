cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(exampleRobotClient LANGUAGES CXX)

if(NOT YARP_FOUND)
    find_package(YARP 3.3 REQUIRED COMPONENTS os dev)
endif()

if(NOT TARGET ASROB::RobotInterfaces)
    find_package(ASROB_YARP_DEVICES REQUIRED)
endif()

add_executable(exampleRobotClient exampleRobotClient.cpp)

target_link_libraries(exampleRobotClient YARP::YARP_os
                                         YARP::YARP_init
                                         YARP::YARP_dev
                                         ASROB::RobotInterfaces)
