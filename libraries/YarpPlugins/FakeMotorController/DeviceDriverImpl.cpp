// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"

namespace asrob
{

bool FakeMotorController::open(yarp::os::Searchable& config)
{
    CD_DEBUG("Got options: %s\n",config.toString().c_str());

    if( config.check("dummy","check dummy option") );
    {
        CD_SUCCESS("Got dummy option.\n");
    }

    return true;
}

bool FakeMotorController::close()
{

    return true;
}

}  // namespace asrob
