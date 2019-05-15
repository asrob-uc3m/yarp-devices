// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RobotClient.hpp"

namespace asrob
{

RobotClient::RobotClient()
{
}

bool RobotClient::moveForward(double value)
{
    CD_DEBUG("%f\n",value);
    return send1vocab1double(VOCAB_MOVE_FORWARD,value);
}

bool RobotClient::turnLeft(double value)
{
    CD_DEBUG("%f\n",value);
    return send1vocab1double(VOCAB_TURN_LEFT,value);
}

bool RobotClient::stopMovement()
{
    CD_DEBUG("\n");
    return send1vocab(VOCAB_STOP_MOVEMENT);
}

bool RobotClient::tiltDown(double value)
{
    CD_DEBUG("%f\n",value);
    return send1vocab1double(VOCAB_TILT_DOWN,value);
}

bool RobotClient::panLeft(double value)
{
    CD_DEBUG("%f\n",value);
    return send1vocab1double(VOCAB_PAN_LEFT,value);
}

bool RobotClient::stopCameraMovement()
{
    CD_DEBUG("\n");
    return send1vocab(VOCAB_STOP_CAMERA_MOVEMENT);
}

bool RobotClient::send1vocab1double(int vocab, double value)
{
    yarp::os::Bottle cmd, response;
    cmd.addVocab(vocab);
    cmd.addFloat64(value);
    rpcClient.write(cmd,response);
    if( response.get(0).asVocab() == VOCAB_OK )
        return true;
    else
        return false;
}

bool RobotClient::send1vocab(int vocab)
{
    yarp::os::Bottle cmd, response;
    cmd.addVocab(vocab);
    rpcClient.write(cmd,response);
    if( response.get(0).asVocab() == VOCAB_OK )
        return true;
    else
        return false;
}

}  // namespace asrob

