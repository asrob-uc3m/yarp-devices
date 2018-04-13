// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "LaserTowerOfDeathController.hpp"

namespace asrob
{

bool LaserTowerOfDeathController::moveForward(double value)
{
    CD_INFO("(%f).\n",value);

    return true;
}

bool LaserTowerOfDeathController::turnLeft(double value)
{
    CD_INFO("(%f).\n",value);

    return true;
}

bool LaserTowerOfDeathController::stopMovement()
{
    CD_INFO(".\n");

    return true;
}

bool LaserTowerOfDeathController::tiltDown(double value)
{
    CD_INFO("\n");
    if (  tiltJointValue > tiltRangeMin )
        tiltJointValue-=tiltStep;

    return sendCurrentJointValues();
}

bool LaserTowerOfDeathController::panLeft(double value)
{
    CD_INFO("\n");
    if (panJointValue < panRangeMax)
        panJointValue+=panStep;

    return sendCurrentJointValues();
}

bool LaserTowerOfDeathController::stopCameraMovement()
{
    CD_ERROR("Not implemented yet\n");
    return false;
}

bool LaserTowerOfDeathController::sendCurrentJointValues()
{
    if ( serialPort->IsOpen() )
    {
        SerialPort::DataBuffer outputBuff;
        outputBuff.push_back(0x50); //-- 0x50 -> Set pos to all joints

        outputBuff.push_back( (char) panJointValue );
        outputBuff.push_back( (char) tiltJointValue );
        serialPort->Write( outputBuff );

        return true;
    }
    else
    {
        CD_WARNING("Robot could not send joints (because it is not connected).\n");
        return false;
    }
}

}  // namespace asrob
