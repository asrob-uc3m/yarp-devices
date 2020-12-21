// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "EcroPwmController.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

bool EcroPwmController::moveForward(double value)
{
    yDebug() << "moveForward" << value;

    if (value <= rightMotorRangeMax && value >= rightMotorRangeMin &&
        value <= leftMotorRangeMax && value >= leftMotorRangeMin)
    {
        rightMotorVelocity = rightMotorOffset + value; //-- 90º angle is 0 speed in driver
        leftMotorVelocity = leftMotorOffset + value;
    }

    return sendCurrentJointValues();
}

bool EcroPwmController::turnLeft(double value)
{
    yDebug() << "turnLeft" << value;

    if (value <= rightMotorRangeMax && value >= rightMotorRangeMin &&
        value <= leftMotorRangeMax && value >= leftMotorRangeMin)
    {
        rightMotorVelocity = rightMotorOffset + value; //-- 90º angle is 0 speed in driver
        leftMotorVelocity = leftMotorOffset - value;
    }

     return sendCurrentJointValues();
}

bool EcroPwmController::stopMovement()
{
    yDebug() << "stopMovement";

    rightMotorVelocity = rightMotorOffset; //-- 90º angle is 0 speed in driver
    leftMotorVelocity = leftMotorOffset;

    return sendCurrentJointValues();
}

//-- Robot camera related functions
bool EcroPwmController::tiltDown(double value)
{
    yDebug() << "tiltDown" << value;
    return true;
}

bool EcroPwmController::panLeft(double value)
{
    yDebug() << "panLeft" << value;
    return true;
}

bool EcroPwmController::stopCameraMovement()
{
    yError() << "stopCameraMovement not implemented yet";
    return false;
}

bool EcroPwmController::sendCurrentJointValues()
{
    if (serialPort->IsOpen())
    {
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x50); //-- 0x50 -> Set pos to all joints

        outputBuff.push_back((char) leftMotorVelocity);
        outputBuff.push_back((char) rightMotorVelocity);
        serialPort->Write( outputBuff );

        return true;
    }
    else
    {
        yWarning() << "Robot could not send joints (because it is not connected)";
        return false;
    }
}

} // namespace asrob
