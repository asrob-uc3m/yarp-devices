// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

bool FakeMotorController::open(yarp::os::Searchable& config)
{
    yDebug() << "Got options:" << config.toString();

    if (config.check("dummy", "check dummy option"))
    {
        yInfo() << "Got dummy option";
    }

    return true;
}

bool FakeMotorController::close()
{
    return true;
}

} // namespace asrob
