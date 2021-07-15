// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "EcroWheelController.hpp"
#include "LogComponent.hpp"

using namespace asrob;

bool EcroWheelController::open(yarp::os::Searchable& config)
{
    std::string serialPortName = config.check("serialPortName", yarp::os::Value(DEFAULT_SERIAL_PORT_NAME), "serialPortName").asString();

    yCInfo(EWC) << "EcroWheelController options:";
    yCInfo(EWC) << "--serialPortName" << serialPortName;

    yCDebug(EWC) << "Init Serial Port";
    serialPort = new SerialPort(serialPortName); // "/dev/ttyUSB0"

    try
    {
        serialPort->Open(SerialPort::BAUD_19200, SerialPort::CHAR_SIZE_8,
                         SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                         SerialPort::FLOW_CONTROL_NONE);
    }
    catch (SerialPort::OpenFailed e)
    {
        yCError(EWC) << "Error opening the serial port" << serialPortName;
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
        yWarning(EWC) << "Robot could not revert wheel command (because it is not connected)";
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
