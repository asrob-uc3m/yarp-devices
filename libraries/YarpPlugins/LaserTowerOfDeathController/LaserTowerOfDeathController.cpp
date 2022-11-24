// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "LaserTowerOfDeathController.hpp"

#include <algorithm> // std::clamp

#include <yarp/os/LogStream.h>

#include "LogComponent.hpp"

using namespace asrob;

constexpr int panRangeMin = 0;
constexpr int panRangeMax = 180;

constexpr int tiltRangeMin = 0;
constexpr int tiltRangeMax = 180;

bool LaserTowerOfDeathController::moveForward(double value)
{
    yCDebug(LTODC) << "moveForward" << value;
    return true;
}

bool LaserTowerOfDeathController::turnLeft(double value)
{
    yCDebug(LTODC) << "turnLeft" << value;
    return true;
}

bool LaserTowerOfDeathController::stopMovement()
{
    yCDebug(LTODC) << "stopMovement";
    return true;
}

bool LaserTowerOfDeathController::tiltDown(double value)
{
    yCDebug(LTODC) << "tiltDown" << static_cast<int>(value);
    tiltJointValue = std::clamp(tiltJointValue - static_cast<int>(value), tiltRangeMin, tiltRangeMax);
    return sendCurrentJointValues();
}

bool LaserTowerOfDeathController::panLeft(double value)
{
    yCDebug(LTODC) << "panLeft" << static_cast<int>(value);
    panJointValue = std::clamp(panJointValue + static_cast<int>(value), panRangeMin, panRangeMax);
    return sendCurrentJointValues();
}

bool LaserTowerOfDeathController::stopCameraMovement()
{
    yCError(LTODC) << "stopCameraMovement not implemented yet";
    return false;
}

bool LaserTowerOfDeathController::sendCurrentJointValues()
{
    //-- 0x50 -> Set pos to all joints
    char msg[] = {0x50, static_cast<char>(panJointValue), static_cast<char>(tiltJointValue)};

    if (!serial->send(msg, sizeof(msg)))
    {
        yCError(LTODC) << "Error sending message";
        return false;
    }

    return true;
}

bool LaserTowerOfDeathController::checkConnection()
{
    //-- Read welcome message to check if connected to the robot
    static const std::string welcomeMessage = "[Debug] Ok!";

    std::string line(welcomeMessage.size(), ' ');

    if (!serial->receiveLine(line.data(), welcomeMessage.size() + 1))
    {
        yCError(LTODC) << "Could not read welcome message from robot";
        return false;
    }

    return line == welcomeMessage;
}
