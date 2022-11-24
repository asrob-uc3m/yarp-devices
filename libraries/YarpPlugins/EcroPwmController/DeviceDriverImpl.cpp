// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "EcroPwmController.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>

#include "LogComponent.hpp"

using namespace asrob;

constexpr auto DEFAULT_SERIAL_PORT_NAME = "/dev/ttyUSB0";

bool EcroPwmController::open(yarp::os::Searchable& config)
{
    auto serialPortName = config.check("serialPortName", yarp::os::Value(DEFAULT_SERIAL_PORT_NAME), "serialPortName").asString();

    yarp::os::Property serialDeviceOptions {
        {"device", yarp::os::Value("serialport")},
        {"comport", yarp::os::Value(serialPortName)},
        {"baudrate", yarp::os::Value(57600)},
        {"paritymode", yarp::os::Value("NONE")},
        {"databits", yarp::os::Value(8)}
    };

    if (!serialDevice.open(serialDeviceOptions))
    {
        yCError(EPC) << "Could not open serial device";
        return false;
    }

    if (!serialDevice.view(serial))
    {
        yCError(EPC) << "Could not view serial interface";
        return false;
    }

    return true;
}

bool EcroPwmController::close()
{
    return serialDevice.close();
}
