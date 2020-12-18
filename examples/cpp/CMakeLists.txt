option(ENABLE_examples "Enable/disable C++ examples" OFF)

if(ENABLE_examples)
    if(TARGET ASROB::RobotInterfaces)
        add_subdirectory(exampleRobotClient)
    endif()
endif()
