// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "EcroWheelController.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

bool EcroWheelController::moveForward(double value)
{
    yDebug() << "moveForward" << value;

    if (serialPort->IsOpen())
    {
        SerialPort::DataBuffer outputBuff;

        outputBuff.push_back(0x20);  // Both Wheels
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.05);

        int16_t positions1 = value;
        int8_t positions1_high = positions1;
        positions1 <<= 8;
        int8_t positions1_low = positions1;

        yDebug("2 bytes: 0x%x", positions1);
        yDebug("high byte: 0x%x", positions1_high);
        yDebug("low byte: 0x%x", positions1_low);

        outputBuff.clear();
        outputBuff.push_back(positions1_low);  // 0x01
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.05);

        outputBuff.clear();
        outputBuff.push_back(positions1_high);  // 0x01
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.05);

        yDebug("high byte");

        return true;
    }
    else
    {
        yWarning() << "Robot could not send joints (because it is not connected)";
        return false;
    }

    return true;
}

bool EcroWheelController::turnLeft(double value)
{
    yDebug() << "turnLeft" << value;

    if (serialPort->IsOpen())
    {
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x21);  // Wheels 1
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.05);

        int16_t positions1 = value;
        int8_t positions1_high = positions1;
        positions1 <<= 8;
        int8_t positions1_low = positions1;

        yDebug("2 bytes: 0x%x", positions1);
        yDebug("high byte: 0x%x", positions1_high);
        yDebug("low byte: 0x%x", positions1_low);

        outputBuff.clear();
        outputBuff.push_back(positions1_low);  // 0x01
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.05);

        outputBuff.clear();
        outputBuff.push_back(positions1_high);  // 0x01
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.05);

        int16_t positions2 = -value;
        int8_t positions2_high = positions2;
        positions2 <<= 8;
        int8_t positions2_low = positions2;

        outputBuff.clear();
        outputBuff.push_back(0x22);  // Wheel2
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.05);

        outputBuff.clear();
        outputBuff.push_back(positions2_low);  // 0x01
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.05);
        outputBuff.clear();
        outputBuff.push_back(positions2_high);  // 0x01
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.05);

        yDebug("high byte");

        return true;
    }
    else
    {
        yWarning() << "Robot could not send joints (because it is not connected)";
        return false;
    }

    return true;
}

bool EcroWheelController::stopMovement()
{
    yDebug() << "stopMovement";

    if (serialPort->IsOpen())
    {
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x32);  // Invert motor 1
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.5);

        outputBuff.clear();
        outputBuff.push_back(0x28);  // Este ambos, 29 limpiaria 1, 30 el 2 ?
        serialPort->Write(outputBuff);
        yarp::os::Time::delay(0.5);
    }
    else
    {
        yWarning() << "Robot could not revert wheel command (because it is not connected)";
        return false;
    }

    return true;
}

//-- Robot camera related functions

bool EcroWheelController::tiltDown(double velocity)
{
    yDebug() << "tiltDown" << velocity;
    return true;
}

bool EcroWheelController::panLeft(double value)
{
    yDebug() << "panLeft" << value;
    return true;
}

bool EcroWheelController::stopCameraMovement()
{
    yError() << "stopCameraMovement not implemented yet";
    return false;
}

} // namespace asrob
