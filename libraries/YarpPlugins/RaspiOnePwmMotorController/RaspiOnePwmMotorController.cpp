// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RaspiOnePwmMotorController.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

bool RaspiOnePwmMotorController::indexWithinRange(const int& idx)
{
    if (idx >= gpios.size())
    {
        yWarning() << "Index out of range!!" << idx << ">=" << gpios.size();
        return false;
    }

    return true;
}

bool RaspiOnePwmMotorController::moveForward(double value)
{
    yDebug() << "moveForward" << value;

    clear_channel_gpio(0, gpios[0]);
    add_channel_pulse(0, gpios[0], 0, 2000 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    clear_channel_gpio(0, gpios[1]);
    add_channel_pulse(0, gpios[1], 0, 1000 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    return true;
}

bool RaspiOnePwmMotorController::turnLeft(double value)
{
    yDebug() << "turnLeft" << value;

    clear_channel_gpio(0, gpios[0]);
    add_channel_pulse(0, gpios[0], 0, 1250 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    clear_channel_gpio(0, gpios[1]);
    add_channel_pulse(0, gpios[1], 0, 1250 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    return true;
}

bool RaspiOnePwmMotorController::stopMovement()
{
    yDebug() << "stopMovement";

    clear_channel_gpio(0, gpios[0]);
    add_channel_pulse(0, gpios[0], 0, 0 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    clear_channel_gpio(0, gpios[1]);
    add_channel_pulse(0, gpios[1], 0, 0 / PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT);

    return true;
}

//-- Robot camera related functions
bool RaspiOnePwmMotorController::tiltDown(double value)
{
    yError() << "tiltDown not implemented yet";
    return false;
}

bool RaspiOnePwmMotorController::panLeft(double value)
{
    yError() << "panLeft not implemented yet";
    return false;
}

bool RaspiOnePwmMotorController::stopCameraMovement()
{
    yError() << "stopCameraMovement not implemented yet";
    return false;
}

} // namespace asrob
