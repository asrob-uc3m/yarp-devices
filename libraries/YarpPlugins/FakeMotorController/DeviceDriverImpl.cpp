// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"
#include "LogComponent.hpp"

using namespace asrob;

bool FakeMotorController::open(yarp::os::Searchable& config)
{
    yCDebug(FMC) << "Config:" << config.toString();

    if (config.check("dummy", "check dummy option"))
    {
        yInfo(FMC) << "Got dummy option";
    }

    return true;
}

bool FakeMotorController::close()
{
    return true;
}
