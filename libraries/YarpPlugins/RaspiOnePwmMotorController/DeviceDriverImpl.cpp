// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RaspiOnePwmMotorController.hpp"
#include "LogComponent.hpp"

using namespace asrob;

bool RaspiOnePwmMotorController::open(yarp::os::Searchable& config)
{
    yarp::os::Bottle gpiosBottle = config.findGroup("gpios").tail(); //-- e.g. 17 27

    yCInfo(ROPMC) << "RaspiOnePwmMotorController options:";
    yCInfo(ROPMC) << "--gpios" << gpiosBottle.toString();

    if (gpiosBottle.size() < 1)
    {
        yCError(ROPMC) << "Please specify at least one gpio";
        return false;
    }

    if (config.check("pcm"))
        setup(PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT, DELAY_VIA_PCM);
    else
        setup(PULSE_WIDTH_INCREMENT_GRANULARITY_US_DEFAULT, DELAY_VIA_PWM);

    init_channel(0, SUBCYCLE_TIME_US_DEFAULT); // 10ms;
    print_channel(0);

    for (int j = 0; j < gpiosBottle.size(); j++)
    {
        int gpio = gpiosBottle.get(j).asInt32();
        add_channel_pulse(0, gpio, 0, 0);
        gpios.push_back(gpiosBottle.get(j).asInt32());
        yCInfo(ROPMC) << "Configured gpio" << gpio << "on channel 0";
    }

    return true;
}

bool RaspiOnePwmMotorController::close()
{
    return true;
}
