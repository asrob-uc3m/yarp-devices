// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "EcroPwmController.hpp"
#include "LogComponent.hpp"

using namespace asrob;

bool EcroPwmController::open(yarp::os::Searchable& config)
{
    std::string serialPortName = config.check("serialPortName", yarp::os::Value(DEFAULT_SERIAL_PORT_NAME), "serialPortName").asString();

    yCInfo(EPC) << "EcroPwmController options:";
    yCInfo(EPC) << "--serialPortName" << serialPortName;

    yCDebug(EPC) << "Init Serial Port";
    serialPort = new SerialPort(serialPortName); // "/dev/ttyUSB0"

    try
    {
        serialPort->Open(SerialPort::BAUD_57600, SerialPort::CHAR_SIZE_8,
                         SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
                         SerialPort::FLOW_CONTROL_NONE);
    }
    catch (SerialPort::OpenFailed e)
    {
        yCError(EPC) << "Error opening the serial port" << serialPortName;
        return false;
    }

    yCInfo(EPC) << "Ok Serial Port:" << serialPortName << "(without check)";

    leftMotorVelocity = leftMotorInitial;
    rightMotorVelocity = rightMotorInitial;

    return true;
}

bool EcroPwmController::close()
{
    serialPort->Close();
    delete serialPort;
    serialPort = 0;
    return true;
}
