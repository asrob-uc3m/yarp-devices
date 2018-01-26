// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"

namespace asrob
{

bool FakeMotorController::open(yarp::os::Searchable& config)
{
    CD_INFO("[FakeMotorController]\n");
    return true;
}

bool FakeMotorController::close()
{

    return true;
}

}  // namespace asrob
