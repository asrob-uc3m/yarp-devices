// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RaspiOnePwmMotorController.hpp"

namespace asrob
{

bool RaspiOnePwmMotorController::indexWithinRange(const int& idx)
{
    if (idx >= gpios.size() ){
        CD_WARNING("Index out of range!! (%d >= " CD_SIZE_T ")!!!\n",idx,gpios.size());
        return false;
    }
    return true;
}

bool RaspiOnePwmMotorController::moveForward(double value)
{
    CD_INFO("(%f).\n",value);

    clear_channel_gpio(0, gpios[0]);
    add_channel_pulse(0, gpios[0], 0, 2000 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    clear_channel_gpio(0, gpios[1]);
    add_channel_pulse(0, gpios[1], 0, 1000 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    return true;
}

bool RaspiOnePwmMotorController::turnLeft(double value)
{
    CD_INFO("(%f).\n",value);

    clear_channel_gpio(0, gpios[0]);
    add_channel_pulse(0, gpios[0], 0, 1250 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    clear_channel_gpio(0, gpios[1]);
    add_channel_pulse(0, gpios[1], 0, 1250 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    return true;
}

bool RaspiOnePwmMotorController::stopMovement()
{
    CD_INFO(".\n");

    clear_channel_gpio(0, gpios[0]);
    add_channel_pulse(0, gpios[0], 0, 0 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    clear_channel_gpio(0, gpios[1]);
    add_channel_pulse(0, gpios[1], 0, 0 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    return true;
}

//-- Robot camera related functions
bool RaspiOnePwmMotorController::tiltDown(double value)
{
    CD_ERROR("Not implemented yet\n");
    return false;
}

bool RaspiOnePwmMotorController::panLeft(double value)
{
    CD_ERROR("Not implemented yet\n");
    return false;
}

bool RaspiOnePwmMotorController::stopCameraMovement()
{
    CD_ERROR("Not implemented yet\n");
    return false;
}

}  // namespace asrob
