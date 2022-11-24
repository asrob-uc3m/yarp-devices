// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "EcroWheelController.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>

#include "LogComponent.hpp"

using namespace asrob;

constexpr auto DEFAULT_SERIAL_PORT_NAME = "/dev/ttyUSB0";

bool EcroWheelController::open(yarp::os::Searchable& config)
{
    auto serialPortName = config.check("serialPortName", yarp::os::Value(DEFAULT_SERIAL_PORT_NAME), "serialPortName").asString();

    yarp::os::Property serialDeviceOptions {
        {"device", yarp::os::Value("serialport")},
        {"comport", yarp::os::Value(serialPortName)},
        {"baudrate", yarp::os::Value(19200)},
        {"paritymode", yarp::os::Value("NONE")},
        {"databits", yarp::os::Value(8)}
    };

    if (!serialDevice.open(serialDeviceOptions))
    {
        yCError(EWC) << "Could not open serial device";
        return false;
    }

    if (!serialDevice.view(serial))
    {
        yCError(EWC) << "Could not view serial interface";
        return false;
    }

    if (!stopMovement())
    {
        yCError(EWC) << "Could not stop movement during initial config";
        return false;
    }

    return true;
}

bool EcroWheelController::close()
{
    return serialDevice.close();
}
