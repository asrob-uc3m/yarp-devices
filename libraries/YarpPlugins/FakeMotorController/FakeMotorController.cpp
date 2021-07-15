// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"
#include "LogComponent.hpp"

using namespace asrob;

bool FakeMotorController::moveForward(double value)
{
    yCDebug(FMC) << "moveForward" << value;
    return true;
}

bool FakeMotorController::turnLeft(double value)
{
    yCDebug(FMC) << "turnLeft" << value;
    return true;
}

bool FakeMotorController::stopMovement()
{
    yCDebug(FMC) << "stopMovement";
    return true;
}

bool FakeMotorController::tiltDown(double value)
{
    yCDebug(FMC) << "tiltDown" << value;
    return true;
}

bool FakeMotorController::panLeft(double value)
{
    yCDebug(FMC) << "panLeft" << value;
    return true;
}

bool FakeMotorController::stopCameraMovement()
{
    yCDebug(FMC) << "stopCameraMovement";
    return true;
}
