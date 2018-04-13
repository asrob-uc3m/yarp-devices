// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"

namespace asrob
{

bool FakeMotorController::moveForward(double value)
{
    CD_INFO("%f.\n",value);
    return true;
}

bool FakeMotorController::turnLeft(double value)
{
    CD_INFO("%f.\n",value);
    return true;
}

bool FakeMotorController::stopMovement()
{
    CD_INFO("\n");
    return true;
}

bool FakeMotorController::tiltDown(double value)
{
    CD_INFO("%f.\n",value);
    return true;
}

bool FakeMotorController::panLeft(double value)
{
    CD_INFO("%f.\n",value);
    return true;
}

bool FakeMotorController::stopCameraMovement()
{
    CD_INFO("\n");
    return true;
}

}  // namespace asrob

