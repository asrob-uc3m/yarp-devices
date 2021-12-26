// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RobotServer.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/dev/GenericVocabs.h>

#include "LogComponent.hpp"

using namespace asrob;

bool RobotServer::read(yarp::os::ConnectionReader& connection)
{
    yarp::os::Bottle in, out;
    bool ok = in.read(connection);

    if (!ok) return false;

    yCDebug(RS) << "Got:" << in.toString();

    if (in.get(0).asString() == "help")
    {
        out.addVocab32(VOCAB_MOVE_FORWARD);
        out.addVocab32(VOCAB_TURN_LEFT);
        out.addVocab32(VOCAB_STOP_MOVEMENT);
        out.addVocab32(VOCAB_TILT_DOWN);
        out.addVocab32(VOCAB_PAN_LEFT);
        out.addVocab32(VOCAB_STOP_CAMERA_MOVEMENT);
    }
    else
    {
        switch (in.get(0).asVocab32())
        {
        case VOCAB_MOVE_FORWARD:
            iRobotManager->moveForward(in.get(1).asFloat64());
            out.addVocab32(VOCAB_OK);
            break;
        case VOCAB_TURN_LEFT:
            iRobotManager->turnLeft(in.get(1).asFloat64());
            out.addVocab32(VOCAB_OK);
            break;
        case VOCAB_STOP_MOVEMENT:
            iRobotManager->stopMovement();
            out.addVocab32(VOCAB_OK);
            break;
        case VOCAB_TILT_DOWN:
            iRobotManager->tiltDown(in.get(1).asFloat64());
            out.addVocab32(VOCAB_OK);
            break;
        case VOCAB_PAN_LEFT:
            iRobotManager->panLeft(in.get(1).asFloat64());
            out.addVocab32(VOCAB_OK);
            break;
        case VOCAB_STOP_CAMERA_MOVEMENT:
            iRobotManager->stopCameraMovement();
            out.addVocab32(VOCAB_OK);
            break;
        default:
            out.addVocab32(VOCAB_FAILED);
            break;
        }
    }

    yarp::os::ConnectionWriter *returnToSender = connection.getWriter();

    if (returnToSender)
    {
        out.write(*returnToSender);
    }

    return true;
}
