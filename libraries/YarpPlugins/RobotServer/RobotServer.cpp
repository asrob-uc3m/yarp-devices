// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RobotServer.hpp"

#include <yarp/conf/version.h>
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
#if YARP_VERSION_MINOR >= 5
        out.addVocab32(VOCAB_MOVE_FORWARD);
        out.addVocab32(VOCAB_TURN_LEFT);
        out.addVocab32(VOCAB_STOP_MOVEMENT);
        out.addVocab32(VOCAB_TILT_DOWN);
        out.addVocab32(VOCAB_PAN_LEFT);
        out.addVocab32(VOCAB_STOP_CAMERA_MOVEMENT);
#else
        out.addVocab(VOCAB_MOVE_FORWARD);
        out.addVocab(VOCAB_TURN_LEFT);
        out.addVocab(VOCAB_STOP_MOVEMENT);
        out.addVocab(VOCAB_TILT_DOWN);
        out.addVocab(VOCAB_PAN_LEFT);
        out.addVocab(VOCAB_STOP_CAMERA_MOVEMENT);
#endif
    }
#if YARP_VERSION_MINOR >= 5
    else if (in.get(0).asVocab32() == VOCAB_MOVE_FORWARD)
#else
    else if (in.get(0).asVocab() == VOCAB_MOVE_FORWARD)
#endif
    {
        iRobotManager->moveForward(in.get(1).asFloat64());
#if YARP_VERSION_MINOR >= 5
        out.addVocab32(VOCAB_OK);
#else
        out.addVocab(VOCAB_OK);
#endif
    }
#if YARP_VERSION_MINOR >= 5
    else if (in.get(0).asVocab32() == VOCAB_TURN_LEFT)
#else
    else if (in.get(0).asVocab() == VOCAB_TURN_LEFT)
#endif
    {
        iRobotManager->turnLeft(in.get(1).asFloat64());
#if YARP_VERSION_MINOR >= 5
        out.addVocab32(VOCAB_OK);
#else
        out.addVocab(VOCAB_OK);
#endif
    }
#if YARP_VERSION_MINOR >= 5
    else if (in.get(0).asVocab32() == VOCAB_STOP_MOVEMENT)
#else
    else if (in.get(0).asVocab() == VOCAB_STOP_MOVEMENT)
#endif
    {
        iRobotManager->stopMovement();
#if YARP_VERSION_MINOR >= 5
        out.addVocab32(VOCAB_OK);
#else
        out.addVocab(VOCAB_OK);
#endif
    }
#if YARP_VERSION_MINOR >= 5
    else if (in.get(0).asVocab32() == VOCAB_TILT_DOWN)
#else
    else if (in.get(0).asVocab() == VOCAB_TILT_DOWN)
#endif
    {
        iRobotManager->tiltDown(in.get(1).asFloat64());
#if YARP_VERSION_MINOR >= 5
        out.addVocab32(VOCAB_OK);
#else
        out.addVocab(VOCAB_OK);
#endif
    }
#if YARP_VERSION_MINOR >= 5
    else if (in.get(0).asVocab32() == VOCAB_PAN_LEFT)
#else
    else if (in.get(0).asVocab() == VOCAB_PAN_LEFT)
#endif
    {
        iRobotManager->panLeft(in.get(1).asFloat64());
#if YARP_VERSION_MINOR >= 5
        out.addVocab32(VOCAB_OK);
#else
        out.addVocab(VOCAB_OK);
#endif
    }
#if YARP_VERSION_MINOR >= 5
    else if (in.get(0).asVocab32() == VOCAB_STOP_CAMERA_MOVEMENT)
#else
    else if (in.get(0).asVocab() == VOCAB_STOP_CAMERA_MOVEMENT)
#endif
    {
        iRobotManager->stopCameraMovement();
#if YARP_VERSION_MINOR >= 5
        out.addVocab32(VOCAB_OK);
#else
        out.addVocab(VOCAB_OK);
#endif
    }
    else
    {
#if YARP_VERSION_MINOR >= 5
        out.addVocab32(VOCAB_FAILED);
#else
        out.addVocab(VOCAB_FAILED);
#endif
    }

    yarp::os::ConnectionWriter *returnToSender = connection.getWriter();

    if (returnToSender != NULL)
    {
        out.write(*returnToSender);
    }

    return true;
}

} // namespace asrob
