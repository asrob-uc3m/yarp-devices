// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "LaserTowerOfDeathController.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

bool LaserTowerOfDeathController::moveForward(double value)
{
    yDebug() << "moveForward" << value;
    return true;
}

bool LaserTowerOfDeathController::turnLeft(double value)
{
    yDebug() << "turnLeft" << value;
    return true;
}

bool LaserTowerOfDeathController::stopMovement()
{
    yDebug() << "stopMovement";
    return true;
}

bool LaserTowerOfDeathController::tiltDown(double value)
{
    yDebug() << "tiltDown" << value;

    if (tiltJointValue - value > tiltRangeMax)
        tiltJointValue = tiltRangeMax;
    else if (tiltJointValue - value < tiltRangeMin)
        tiltJointValue = tiltRangeMin;
    else
        tiltJointValue -= value;

    return sendCurrentJointValues();
}

bool LaserTowerOfDeathController::panLeft(double value)
{
    yDebug() << "panLeft" << value;

    if (panJointValue + value > panRangeMax)
        panJointValue = panRangeMax;
    else if (panJointValue + value < panRangeMin)
        panJointValue = panRangeMin;
    else
        panJointValue += value;

    return sendCurrentJointValues();
}

bool LaserTowerOfDeathController::stopCameraMovement()
{
    yError() << "stopCameraMovement not implemented yet";
    return false;
}

bool LaserTowerOfDeathController::sendCurrentJointValues()
{
    if (serialPort->IsOpen())
    {
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x50); //-- 0x50 -> Set pos to all joints

        outputBuff.push_back((char) panJointValue);
        outputBuff.push_back((char) tiltJointValue);
        serialPort->Write(outputBuff);

        return true;
    }
    else
    {
        yWarning() << "Robot could not send joints (because it is not connected)";
        return false;
    }
}

bool LaserTowerOfDeathController::checkConnection()
{
    //-- Read welcome message to check if connected to the robot
    SerialPort::DataBuffer buffer;

    try
    {
        serialPort->Read(buffer, 13, 1500);
    }
    catch (SerialPort::ReadTimeout e)
    {
        yError() << "Timeout! Exiting...";
        return false;
    }

    //-- Check if connected
    std::string welcomeMessage = "[Debug] Ok!\r\n";
    bool diffFlag = false;

    for (int i = 0; i < (int) buffer.size(); i++)
    {
        if (welcomeMessage[i] != buffer[i])
        {
            diffFlag = true;
        }
    }

    return !diffFlag;
}

} // namespace asrob
