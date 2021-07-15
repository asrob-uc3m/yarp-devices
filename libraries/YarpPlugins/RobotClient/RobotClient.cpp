// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RobotClient.hpp"

#include <yarp/conf/version.h>

#include "LogComponent.hpp"

using namespace asrob;

bool RobotClient::moveForward(double value)
{
    yCDebug(RC) << "moveForward" << value;
    return send1vocab1double(VOCAB_MOVE_FORWARD, value);
}

bool RobotClient::turnLeft(double value)
{
    yCDebug(RC) << "turnLeft" << value;
    return send1vocab1double(VOCAB_TURN_LEFT, value);
}

bool RobotClient::stopMovement()
{
    yCDebug(RC) << "stopMovement";
    return send1vocab(VOCAB_STOP_MOVEMENT);
}

bool RobotClient::tiltDown(double value)
{
    yCDebug(RC) << "tiltDown" << value;
    return send1vocab1double(VOCAB_TILT_DOWN, value);
}

bool RobotClient::panLeft(double value)
{
    yCDebug(RC) << "panLeft" << value;
    return send1vocab1double(VOCAB_PAN_LEFT, value);
}

bool RobotClient::stopCameraMovement()
{
    yCDebug(RC) << "stopCameraMovement";
    return send1vocab(VOCAB_STOP_CAMERA_MOVEMENT);
}

bool RobotClient::send1vocab1double(int vocab, double value)
{
    yarp::os::Bottle cmd, response;
#if YARP_VERSION_MINOR >= 5
    cmd.addVocab32(vocab);
#else
    cmd.addVocab(vocab);
#endif
    cmd.addFloat64(value);
    rpcClient.write(cmd, response);

#if YARP_VERSION_MINOR >= 5
    if (response.get(0).asVocab32() == VOCAB_OK)
#else
    if (response.get(0).asVocab() == VOCAB_OK)
#endif
        return true;
    else
        return false;
}

bool RobotClient::send1vocab(int vocab)
{
    yarp::os::Bottle cmd, response;
#if YARP_VERSION_MINOR >= 5
    cmd.addVocab32(vocab);
#else
    cmd.addVocab(vocab);
#endif
    rpcClient.write(cmd, response);

#if YARP_VERSION_MINOR >= 5
    if (response.get(0).asVocab32() == VOCAB_OK)
#else
    if (response.get(0).asVocab() == VOCAB_OK)
#endif
        return true;
    else
        return false;
}
