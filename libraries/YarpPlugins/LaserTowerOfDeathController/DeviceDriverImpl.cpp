// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "LaserTowerOfDeathController.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace asrob;

constexpr auto DEFAULT_SERIAL_PORT_NAME = "/dev/ttyUSB0";

bool LaserTowerOfDeathController::open(yarp::os::Searchable& config)
{
    std::string serialPortName = config.check("serialPortName", yarp::os::Value(DEFAULT_SERIAL_PORT_NAME), "serialPortName").asString();

    yCInfo(LTODC) << "LaserTowerOfDeathController options:";
    yCInfo(LTODC) << "--serialPortName" << serialPortName;

    yCDebug(LTODC) << "Init Serial Port";
    serialPort = new SerialPort(serialPortName); // "/dev/ttyUSB0"

    try
    {
        serialPort->Open(SerialPort::BAUD_57600, SerialPort::CHAR_SIZE_8,
                         SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                         SerialPort::FLOW_CONTROL_NONE);
    }
    catch (SerialPort::OpenFailed e)
    {
        yCError(LTODC) << "Error opening the serial port:" << serialPortName;
        return false;
    }

    if (!checkConnection())
    {
        yCError(LTODC) << "Error communicating with the robot. Exiting...";
        return false;
    }

    yCInfo(LTODC) << "Ok Serial Port" << serialPortName;

    panJointValue = panInitial;
    tiltJointValue = tiltInitial;

    return true;
}

bool LaserTowerOfDeathController::close()
{
    serialPort->Close();
    delete serialPort;
    serialPort = nullptr;
    return true;
}
