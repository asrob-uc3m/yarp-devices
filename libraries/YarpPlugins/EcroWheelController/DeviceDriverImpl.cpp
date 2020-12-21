// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "EcroWheelController.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

bool EcroWheelController::open(yarp::os::Searchable& config)
{
    std::string serialPortName = config.check("serialPortName", yarp::os::Value(DEFAULT_SERIAL_PORT_NAME), "serialPortName").asString();

    yInfo() << "EcroWheelController options:";
    yInfo() << "--serialPortName" << serialPortName;

    yDebug() << "Init Serial Port";
    serialPort = new SerialPort(serialPortName); // "/dev/ttyUSB0"

    try
    {
        serialPort->Open(SerialPort::BAUD_19200, SerialPort::CHAR_SIZE_8,
                         SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                         SerialPort::FLOW_CONTROL_NONE);
    }
    catch (SerialPort::OpenFailed e)
    {
        yError() << "Error opening the serial port" << serialPortName;
        return false;
    }

    if (serialPort->IsOpen())
    {
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x32);  // Invert motor 1
        serialPort->Write( outputBuff );
        yarp::os::Time::delay(0.5);

        outputBuff.clear();
        outputBuff.push_back(0x28);  // Este ambos, 29 limpiaria 1, 30 el 2 ?
        serialPort->Write( outputBuff );
        yarp::os::Time::delay(0.5);

    }
    else
    {
        yWarning() << "Robot could not revert wheel command (because it is not connected)";
        return false;
    }

    return true;
}

bool EcroWheelController::close()
{
    serialPort->Close();
    delete serialPort;
    serialPort = 0;
    return true;
}

} // namespace asrob
