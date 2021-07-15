// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RaspiTwoPwmMotorController.hpp"
#include "LogComponent.hpp"

using namespace asrob;

const int RaspiTwoPwmMotorController::LEFT_MOTOR_IN1 = 24;
const int RaspiTwoPwmMotorController::LEFT_MOTOR_IN2 = 23;

const int RaspiTwoPwmMotorController::RIGHT_MOTOR_IN1 = 22;
const int RaspiTwoPwmMotorController::RIGHT_MOTOR_IN2 = 21;

bool RaspiTwoPwmMotorController::indexWithinRange(const int& idx)
{
    if (idx >= gpios.size())
    {
        yCWarning(RTPMC) << "Index out of range!!" << idx << ">=" << gpios.size();
        return false;
    }

    return true;
}

bool RaspiTwoPwmMotorController::moveForward(double value)
{
    yCDebug(RTPMC) << "moveForward" << value;

    digitalWrite(LEFT_MOTOR_IN1, 1);
    digitalWrite(LEFT_MOTOR_IN2, 0);
    digitalWrite(RIGHT_MOTOR_IN1, 1);
    digitalWrite(RIGHT_MOTOR_IN2, 0);
    return true;
}

bool RaspiTwoPwmMotorController::turnLeft(double value)
{
    yCDebug(RTPMC) << "turnLeft" << value;

    digitalWrite(LEFT_MOTOR_IN1, 0);
    digitalWrite(LEFT_MOTOR_IN2, 1);
    digitalWrite(RIGHT_MOTOR_IN1, 1);
    digitalWrite(RIGHT_MOTOR_IN2, 0);

    return true;
}

bool RaspiTwoPwmMotorController::stopMovement()
{
    yCDebug(RTPMC) << "stopMovement";

    digitalWrite(LEFT_MOTOR_IN1, 1);
    digitalWrite(LEFT_MOTOR_IN2, 1);
    digitalWrite(RIGHT_MOTOR_IN1, 1);
    digitalWrite(RIGHT_MOTOR_IN2, 1);

    return true;
}

//-- Robot camera related functions
bool RaspiTwoPwmMotorController::tiltDown(double value)
{
    yCError(RTPMC) << "tiltDown not implemented yet";
    return false;
}

bool RaspiTwoPwmMotorController::panLeft(double value)
{
    yCError(RTPMC) << "panLeft not implemented yet";
    return false;
}

bool RaspiTwoPwmMotorController::stopCameraMovement()
{
    yCError(RTPMC) << "stopCameraMovement not implemented yet";
    return false;
}
