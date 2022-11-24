// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "EcroPwmController.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace asrob;

constexpr int leftMotorRangeMin = 0;
constexpr int leftMotorRangeMax = 90;

constexpr int rightMotorRangeMin = 0;
constexpr int rightMotorRangeMax = 90;

constexpr int leftMotorOffset = 90;
constexpr int rightMotorOffset = 90;

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
    char msg[] = {0x50, static_cast<char>(leftMotorVelocity), static_cast<char>(rightMotorVelocity)};

    if (!serial->send(msg, sizeof(msg)))
    {
        yCError(EPC) << "Error sending message";
        return false;
    }

    return true;
}
