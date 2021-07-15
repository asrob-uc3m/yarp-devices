// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "EcroPwmController.hpp"
#include "LogComponent.hpp"

using namespace asrob;

bool EcroPwmController::moveForward(double value)
{
    yCDebug(EPC) << "moveForward" << value;

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
    yCDebug(EPC) << "turnLeft" << value;

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
    yCDebug(EPC) << "stopMovement";

    rightMotorVelocity = rightMotorOffset; //-- 90º angle is 0 speed in driver
    leftMotorVelocity = leftMotorOffset;

    return sendCurrentJointValues();
}

//-- Robot camera related functions
bool EcroPwmController::tiltDown(double value)
{
    yCDebug(EPC) << "tiltDown" << value;
    return true;
}

bool EcroPwmController::panLeft(double value)
{
    yCDebug(EPC) << "panLeft" << value;
    return true;
}

bool EcroPwmController::stopCameraMovement()
{
    yCError(EPC) << "stopCameraMovement not implemented yet";
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
        yCWarning(EPC) << "Robot could not send joints (because it is not connected)";
        return false;
    }
}
