// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RaspiTwoPwmMotorController.hpp"
#include "LogComponent.hpp"

using namespace asrob;

bool RaspiTwoPwmMotorController::open(yarp::os::Searchable& config)
{
    yarp::os::Bottle gpiosBottle = config.findGroup("gpios").tail(); //-- e.g. 17 27

    yCInfo(RTPMC) << "RaspiTwoPwmMotorController options:";
    yCInfo(RTPMC) << "--gpios" << gpiosBottle.toString();

    if (gpiosBottle.size() < 1)
    {
        yCError(RTPMC) << "Please specify at least one gpio";
        return false;
    }

    if (wiringPiSetup() == -1)
    {
        return false;
    }

    pinMode(RaspiTwoPwmMotorController::LEFT_MOTOR_IN1, OUTPUT);
    pinMode(RaspiTwoPwmMotorController::LEFT_MOTOR_IN2, OUTPUT);
    pinMode(RaspiTwoPwmMotorController::RIGHT_MOTOR_IN1, OUTPUT);
    pinMode(RaspiTwoPwmMotorController::RIGHT_MOTOR_IN2, OUTPUT);

    return true;
}

bool RaspiTwoPwmMotorController::close()
{
    return true;
}
