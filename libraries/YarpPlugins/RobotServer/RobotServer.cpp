// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RobotServer.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

bool RobotServer::read(yarp::os::ConnectionReader& connection)
{
    yarp::os::Bottle in, out;
    bool ok = in.read(connection);
    if (!ok) return false;

    // process data "in", prepare "out"
    yDebug() << "Got:" << in.toString();

    if (in.get(0).asString() == "help")
    {
        out.addVocab(VOCAB_MOVE_FORWARD);
        out.addVocab(VOCAB_TURN_LEFT);
        out.addVocab(VOCAB_STOP_MOVEMENT);
        out.addVocab(VOCAB_TILT_DOWN);
        out.addVocab(VOCAB_PAN_LEFT);
        out.addVocab(VOCAB_STOP_CAMERA_MOVEMENT);
    }
    else if (in.get(0).asVocab() == VOCAB_MOVE_FORWARD)
    {
        iRobotManager->moveForward(in.get(1).asDouble());
        out.addVocab(VOCAB_OK);
    }
    else if (in.get(0).asVocab() == VOCAB_TURN_LEFT)
    {
        iRobotManager->turnLeft(in.get(1).asDouble());
        out.addVocab(VOCAB_OK);
    }
    else if (in.get(0).asVocab() == VOCAB_STOP_MOVEMENT)
    {
        iRobotManager->stopMovement();
        out.addVocab(VOCAB_OK);
    }
    else if (in.get(0).asVocab() == VOCAB_TILT_DOWN)
    {
        iRobotManager->tiltDown(in.get(1).asDouble());
        out.addVocab(VOCAB_OK);
    }
    else if (in.get(0).asVocab() == VOCAB_PAN_LEFT)
    {
        iRobotManager->panLeft(in.get(1).asDouble());
        out.addVocab(VOCAB_OK);
    }
    else if (in.get(0).asVocab() == VOCAB_STOP_CAMERA_MOVEMENT)
    {
        iRobotManager->stopCameraMovement();
        out.addVocab(VOCAB_OK);
    }
    else
    {
        out.addVocab(VOCAB_FAILED);
    }

    yarp::os::ConnectionWriter *returnToSender = connection.getWriter();

    if (returnToSender != NULL)
    {
        out.write(*returnToSender);
    }

    return true;
}

} // namespace asrob
