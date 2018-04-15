#include "JumpingSumo.hpp"

#include <ColorDebug.hpp>

using namespace asrob;

namespace
{
    const int DEFAULT_VELOCITY = 50;
}

bool JumpingSumo::moveForward(double velocity)
{
    CD_DEBUG("\n");
    const int fixedVelocity = velocity >= 0.0 ? DEFAULT_VELOCITY : -DEFAULT_VELOCITY;
    bool ok = true;
    ok &= deviceController->jumpingSumo->setPilotingPCMDFlag(deviceController->jumpingSumo, 1);
    ok &= deviceController->jumpingSumo->setPilotingPCMDSpeed(deviceController->jumpingSumo, fixedVelocity);
    return ok;
}

bool JumpingSumo::turnLeft(double velocity)
{
    CD_DEBUG("\n");
    const int fixedVelocity = velocity >= 0.0 ? DEFAULT_VELOCITY : -DEFAULT_VELOCITY;
    bool ok = true;
    ok &= deviceController->jumpingSumo->setPilotingPCMDFlag(deviceController->jumpingSumo, 1);
    ok &= deviceController->jumpingSumo->setPilotingPCMDTurn(deviceController->jumpingSumo, -fixedVelocity);
    return ok;
}

bool JumpingSumo::stopMovement()
{
    CD_DEBUG("\n");
    bool ok = true;
    ok &= deviceController->jumpingSumo->setPilotingPCMDFlag(deviceController->jumpingSumo, 0);
    ok &= deviceController->jumpingSumo->setPilotingPCMDSpeed(deviceController->jumpingSumo, 0);
    ok &= deviceController->jumpingSumo->setPilotingPCMDTurn(deviceController->jumpingSumo, 0);
    return ok;
}

bool JumpingSumo::tiltDown(double velocity)
{
    CD_DEBUG("\n");
    return false;
}

bool JumpingSumo::panLeft(double velocity)
{
    CD_DEBUG("\n");
    return false;
}

bool JumpingSumo::stopCameraMovement()
{
    CD_DEBUG("\n");
    return false;
}
