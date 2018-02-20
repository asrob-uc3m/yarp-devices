cmake_minimum_required (VERSION 2.9 FATAL_ERROR)

find_package(Java REQUIRED)
include(UseJava)

project(ExampleRobotClient)

find_file(YARP_JAR_LIBRARY NAMES yarp.jar
                           HINTS YARP_JAVA_BINDINGS
                                 $ENV{YARP_JAVA_BINDINGS}
                           PATHS /usr/share
                                 /usr/local/share
                           PATH_SUFFIXES java
                                         yarp/java)

if(YARP_JAR_LIBRARY)
    message(STATUS "YARP Java bindings found at: ${YARP_JAR_LIBRARY}")
else()
    message(FATAL_ERROR "YARP bindings not found, set YARP_JAVA_BINDINGS variable to a path that points to yarp.jar.")
endif()

find_library(ASROB_YARP_DEVICES_JNI_LIBRARY NAMES asrob_yarp_devices
                                            HINTS $ENV{ASROB_YARP_DEVICES_JAVA_BINDINGS}
                                            PATHS /usr/share
                                                  /usr/local/share
                                            PATH_SUFFIXES java
                                                          yarp/java)

find_path(ASROB_YARP_DEVICES_CLASSPATH NAMES asrob_yarp_devices.class
                                             asrob_yarp_devices.jar
                                       HINTS ASROB_YARP_DEVICES_JAVA_BINDINGS
                                             $ENV{ASROB_YARP_DEVICES_JAVA_BINDINGS}
                                       PATH_SUFFIXES asrob_yarp_devices)

if(ASROB_YARP_DEVICES_CLASSPATH)
    message(STATUS "ASROB_YARP_DEVICES Java bindings found at: ${ASROB_YARP_DEVICES_CLASSPATH}")
else()
    message(FATAL_ERROR "ASROB_YARP_DEVICES bindings not found." "Set ASROB_YARP_DEVICES_JAVA_BINDINGS variable to a path that points to asrob_yarp_devices class files or jars.")
endif()

set(CMAKE_JAVA_INCLUDE_PATH ${YARP_JAR_LIBRARY} ${ASROB_YARP_DEVICES_CLASSPATH})

add_jar(ExampleRobotClient ExampleRobotClient.java ENTRY_POINT ExampleRobotClient)

get_target_property(_jarFile ExampleRobotClient JAR_FILE)
get_target_property(_classDir ExampleRobotClient CLASSDIR)

message(STATUS "Jar file ${_jarFile}")
message(STATUS "Class compiled to ${_classDir}")
