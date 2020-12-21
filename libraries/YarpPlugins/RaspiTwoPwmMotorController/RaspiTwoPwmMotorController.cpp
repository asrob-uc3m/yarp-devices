// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RaspiTwoPwmMotorController.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

const int RaspiTwoPwmMotorController::LEFT_MOTOR_IN1 = 24;
const int RaspiTwoPwmMotorController::LEFT_MOTOR_IN2 = 23;

const int RaspiTwoPwmMotorController::RIGHT_MOTOR_IN1 = 22;
const int RaspiTwoPwmMotorController::RIGHT_MOTOR_IN2 = 21;

bool RaspiTwoPwmMotorController::indexWithinRange(const int& idx)
{
    if (idx >= gpios.size())
    {
        yWarning() << "Index out of range!!" << idx << ">=" << gpios.size();
        return false;
    }

    return true;
}

bool RaspiTwoPwmMotorController::moveForward(double value)
{
    yDebug() << "moveForward" << value;

    digitalWrite(LEFT_MOTOR_IN1, 1);
    digitalWrite(LEFT_MOTOR_IN2, 0);
    digitalWrite(RIGHT_MOTOR_IN1, 1);
    digitalWrite(RIGHT_MOTOR_IN2, 0);
    return true;
}

bool RaspiTwoPwmMotorController::turnLeft(double value)
{
    yDebug() << "turnLeft" << value;

    digitalWrite(LEFT_MOTOR_IN1, 0);
    digitalWrite(LEFT_MOTOR_IN2, 1);
    digitalWrite(RIGHT_MOTOR_IN1, 1);
    digitalWrite(RIGHT_MOTOR_IN2, 0);

    return true;
}

bool RaspiTwoPwmMotorController::stopMovement()
{
    yDebug() << "stopMovement";

    digitalWrite(LEFT_MOTOR_IN1, 1);
    digitalWrite(LEFT_MOTOR_IN2, 1);
    digitalWrite(RIGHT_MOTOR_IN1, 1);
    digitalWrite(RIGHT_MOTOR_IN2, 1);

    return true;
}

//-- Robot camera related functions
bool RaspiTwoPwmMotorController::tiltDown(double value)
{
    yError() << "tiltDown not implemented yet";
    return false;
}

bool RaspiTwoPwmMotorController::panLeft(double value)
{
    yError() << "panLeft not implemented yet";
    return false;
}

bool RaspiTwoPwmMotorController::stopCameraMovement()
{
    yError() << "stopCameraMovement not implemented yet";
    return false;
}

} // namespace asrob
