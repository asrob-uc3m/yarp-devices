// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"

namespace asrob
{

bool FakeMotorController::moveForward(double value)
{
    CD_INFO("%d.\n",value);
    return true;
}

bool FakeMotorController::turnLeft(double value)
{
    CD_INFO("%d.\n",value);
    return true;
}

bool FakeMotorController::stopMovement()
{
    CD_INFO("\n");
    return true;
}

bool FakeMotorController::tiltUp(double value)
{
    CD_INFO("%d.\n",value);
    return true;
}

bool FakeMotorController::panLeft(double value)
{
    CD_INFO("%d.\n",value);
    return true;
}

bool FakeMotorController::stopCameraMovement()
{
    CD_INFO("\n");
    return true;
}

bool FakeMotorController::connect()
{
    CD_INFO("\n");
    return true;
}


bool FakeMotorController::disconnect()
{
    CD_INFO("\n");
    return true;
}

bool FakeMotorController::test()
{
    CD_INFO("\n");
    return true;
}

void FakeMotorController::setEnabled(bool enabled)
{
    CD_INFO("\n");
    return;
}

void FakeMotorController::onDestroy()
{
    CD_INFO("\n");
    return;
}

}  // namespace asrob

