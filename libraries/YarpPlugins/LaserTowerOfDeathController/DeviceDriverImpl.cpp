// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "LaserTowerOfDeathController.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>

#include "LogComponent.hpp"

using namespace asrob;

constexpr auto DEFAULT_SERIAL_PORT_NAME = "/dev/ttyUSB0";

bool LaserTowerOfDeathController::open(yarp::os::Searchable& config)
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
        yCError(LTODC) << "Could not open serial device";
        return false;
    }

    if (!serialDevice.view(serial))
    {
        yCError(LTODC) << "Could not view serial interface";
        return false;
    }

    if (!checkConnection())
    {
        yCError(LTODC) << "Error communicating with the robot";
        return false;
    }

    return true;
}

bool LaserTowerOfDeathController::close()
{
    return serialDevice.close();
}
