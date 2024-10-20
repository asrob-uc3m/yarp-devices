// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace asrob;

bool FakeMotorController::open(yarp::os::Searchable& config)
{
    if (config.check("dummy", "check dummy option"))
    {
        yCInfo(FMC) << "Got dummy option";
    }

    return true;
}

bool FakeMotorController::close()
{
    return true;
}
