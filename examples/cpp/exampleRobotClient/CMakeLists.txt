cmake_minimum_required(VERSION 3.12)

project(exampleRobotClient LANGUAGES CXX)

find_package(YARP 3.3 REQUIRED COMPONENTS os dev sig)
find_package(ASROB_YARP_DEVICES REQUIRED)

add_executable(exampleRobotClient exampleRobotClient.cpp)

target_link_libraries(exampleRobotClient YARP::YARP_os
                                         YARP::YARP_init
                                         YARP::YARP_dev
                                         ASROB::RobotInterfaces)
