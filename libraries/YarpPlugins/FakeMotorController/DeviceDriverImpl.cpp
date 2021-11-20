// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"

#include <yarp/conf/version.h>

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace asrob;

bool FakeMotorController::open(yarp::os::Searchable& config)
{
#if !defined(YARP_VERSION_COMPARE) // < 3.6.0
    yCDebug(FMC) << "Config:" << config.toString();
#endif

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
