// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "EcroPwmController.hpp"

namespace asrob
{

bool EcroPwmController::moveForward(double value)
{
    CD_INFO("\n");
    if (value <= rightMotorRangeMax && value >= rightMotorRangeMin &&
        value <= leftMotorRangeMax && value >= leftMotorRangeMin )
    {
        rightMotorVelocity = rightMotorOffset+value; //-- 90º angle is 0 speed in driver
        leftMotorVelocity = leftMotorOffset+value;
    }

    return sendCurrentJointValues();
}

bool EcroPwmController::turnLeft(double value)
{
    CD_INFO("\n");
    if (value <= rightMotorRangeMax && value >= rightMotorRangeMin &&
        value <= leftMotorRangeMax && value >= leftMotorRangeMin )
    {
        rightMotorVelocity = rightMotorOffset+value; //-- 90º angle is 0 speed in driver
        leftMotorVelocity = leftMotorOffset-value;
    }

     return sendCurrentJointValues();
}

bool EcroPwmController::stopMovement()
{
    CD_INFO("\n");
    rightMotorVelocity = rightMotorOffset; //-- 90º angle is 0 speed in driver
    leftMotorVelocity = leftMotorOffset;

    return sendCurrentJointValues();
}

//-- Robot camera related functions
bool EcroPwmController::tiltDown(double value)
{
    CD_INFO("(%f).\n",value);

    return true;
}

bool EcroPwmController::panLeft(double value)
{
    CD_INFO("(%f).\n",value);

    return true;
}

bool EcroPwmController::stopCameraMovement()
{
    CD_ERROR("Not implemented yet\n");
    return false;
}

bool EcroPwmController::sendCurrentJointValues()
{
    if ( serialPort->IsOpen() )
    {
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x50); //-- 0x50 -> Set pos to all joints

        outputBuff.push_back( (char) leftMotorVelocity );
        outputBuff.push_back( (char) rightMotorVelocity );
        serialPort->Write( outputBuff );

        return true;
    }
    else
    {
        CD_WARNING("Robot could not send joints (because it is not connected).\n");
        return false;
    }
}

}  // namespace asrob
