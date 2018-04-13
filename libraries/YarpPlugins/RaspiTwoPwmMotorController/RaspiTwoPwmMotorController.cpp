// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RaspiTwoPwmMotorController.hpp"

namespace asrob
{

const int RaspiTwoPwmMotorController::LEFT_MOTOR_IN1 = 24;
const int RaspiTwoPwmMotorController::LEFT_MOTOR_IN2 = 23;

const int RaspiTwoPwmMotorController::RIGHT_MOTOR_IN1 = 22;
const int RaspiTwoPwmMotorController::RIGHT_MOTOR_IN2 = 21;

bool RaspiTwoPwmMotorController::indexWithinRange(const int& idx)
{
    if (idx >= gpios.size() ){
        CD_WARNING("Index out of range!! (%d >= " CD_SIZE_T ")!!!\n",idx,gpios.size());
        return false;
    }
    return true;
}


bool RaspiTwoPwmMotorController::moveForward(double value)
{
    CD_INFO("(%d).\n",value);

    digitalWrite(LEFT_MOTOR_IN1, 1);
    digitalWrite(LEFT_MOTOR_IN2, 0);
    digitalWrite(RIGHT_MOTOR_IN1, 1);
    digitalWrite(RIGHT_MOTOR_IN2, 0);
    return true;
}

bool RaspiTwoPwmMotorController::turnLeft(double value)
{
    CD_INFO("(%d).\n",value);

    digitalWrite(LEFT_MOTOR_IN1, 0);
    digitalWrite(LEFT_MOTOR_IN2, 1);
    digitalWrite(RIGHT_MOTOR_IN1, 1);
    digitalWrite(RIGHT_MOTOR_IN2, 0);

    return true;
}

bool RaspiTwoPwmMotorController::stopMovement()
{
    CD_INFO(".\n");

    digitalWrite(LEFT_MOTOR_IN1, 1);
    digitalWrite(LEFT_MOTOR_IN2, 1);
    digitalWrite(RIGHT_MOTOR_IN1, 1);
    digitalWrite(RIGHT_MOTOR_IN2, 1);

    return true;
}

//-- Robot camera related functions
bool RaspiTwoPwmMotorController::tiltDown(double value)
{
    CD_ERROR("Not implemented yet\n");
    return false;
}

bool RaspiTwoPwmMotorController::panLeft(double value)
{
    CD_ERROR("Not implemented yet\n");
    return false;
}

bool RaspiTwoPwmMotorController::stopCameraMovement()
{
    CD_ERROR("Not implemented yet\n");
    return false;
}

}  // namespace asrob
