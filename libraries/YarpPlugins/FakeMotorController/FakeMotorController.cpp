// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "FakeMotorController.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

bool FakeMotorController::moveForward(double value)
{
    yDebug() << "moveForward" << value;
    return true;
}

bool FakeMotorController::turnLeft(double value)
{
    yDebug() << "turnLeft" << value;
    return true;
}

bool FakeMotorController::stopMovement()
{
    yDebug() << "stopMovement";
    return true;
}

bool FakeMotorController::tiltDown(double value)
{
    yDebug() << "tiltDown" << value;
    return true;
}

bool FakeMotorController::panLeft(double value)
{
    yDebug() << "panLeft" << value;
    return true;
}

bool FakeMotorController::stopCameraMovement()
{
    yDebug() << "stopCameraMovement";
    return true;
}

} // namespace asrob
