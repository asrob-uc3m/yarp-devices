// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RaspiOnePwmMotorController.hpp"
#include "LogComponent.hpp"

using namespace asrob;

bool RaspiOnePwmMotorController::indexWithinRange(const int& idx)
{
    if (idx >= gpios.size())
    {
        yCWarning(ROPMC) << "Index out of range!!" << idx << ">=" << gpios.size();
        return false;
    }

    return true;
}

bool RaspiOnePwmMotorController::moveForward(double value)
{
    yCDebug(ROPMC) << "moveForward" << value;

    clear_channel_gpio(0, gpios[0]);
    add_channel_pulse(0, gpios[0], 0, 2000 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    clear_channel_gpio(0, gpios[1]);
    add_channel_pulse(0, gpios[1], 0, 1000 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    return true;
}

bool RaspiOnePwmMotorController::turnLeft(double value)
{
    yCDebug(ROPMC) << "turnLeft" << value;

    clear_channel_gpio(0, gpios[0]);
    add_channel_pulse(0, gpios[0], 0, 1250 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    clear_channel_gpio(0, gpios[1]);
    add_channel_pulse(0, gpios[1], 0, 1250 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    return true;
}

bool RaspiOnePwmMotorController::stopMovement()
{
    yCDebug(ROPMC) << "stopMovement";

    clear_channel_gpio(0, gpios[0]);
    add_channel_pulse(0, gpios[0], 0, 0 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    clear_channel_gpio(0, gpios[1]);
    add_channel_pulse(0, gpios[1], 0, 0 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    return true;
}

//-- Robot camera related functions
bool RaspiOnePwmMotorController::tiltDown(double value)
{
    yCError(ROPMC) << "tiltDown not implemented yet";
    return false;
}

bool RaspiOnePwmMotorController::panLeft(double value)
{
    yCError(ROPMC) << "panLeft not implemented yet";
    return false;
}

bool RaspiOnePwmMotorController::stopCameraMovement()
{
    yCError(ROPMC) << "stopCameraMovement not implemented yet";
    return false;
}
