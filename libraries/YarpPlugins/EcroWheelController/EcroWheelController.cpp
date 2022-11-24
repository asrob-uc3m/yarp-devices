// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "EcroWheelController.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/os/SystemClock.h>

#include "LogComponent.hpp"

using namespace asrob;

constexpr int panRangeMin = 0;
constexpr int panRangeMax = 180;
constexpr int panStep = 10;
constexpr int panInitial = 90;

constexpr int tiltRangeMin = 0;
constexpr int tiltRangeMax = 180;
constexpr int tiltStep = 10;
constexpr int tiltInitial = 90;

bool EcroWheelController::moveForward(double value)
{
    yCDebug(EWC) << "moveForward" << value;

    char msg[1];

    msg[0] = 0x20; // Both Wheels
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.05);

    int16_t positions1 = value;
    int8_t positions1_high = positions1;
    positions1 <<= 8;
    int8_t positions1_low = positions1;

    yCDebug(EWC, "2 bytes: 0x%x", positions1);
    yCDebug(EWC, "high byte: 0x%x", positions1_high);
    yCDebug(EWC, "low byte: 0x%x", positions1_low);

    msg[0] = positions1_low; // 0x01
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.05);

    msg[0] = positions1_high; // 0x00
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.05);

    yCDebug(EWC) << "high byte";
    return true;
}

bool EcroWheelController::turnLeft(double value)
{
    yCDebug(EWC) << "turnLeft" << value;

    char msg[1];

    msg[0] = 0x21; // Wheel 1
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.05);

    int16_t positions1 = value;
    int8_t positions1_high = positions1;
    positions1 <<= 8;
    int8_t positions1_low = positions1;

    yCDebug(EWC, "2 bytes: 0x%x", positions1);
    yCDebug(EWC, "high byte: 0x%x", positions1_high);
    yCDebug(EWC, "low byte: 0x%x", positions1_low);

    msg[0] = positions1_low; // 0x01
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.05);

    msg[0] = positions1_high; // 0x01
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.05);

    int16_t positions2 = -value;
    int8_t positions2_high = positions2;
    positions2 <<= 8;
    int8_t positions2_low = positions2;

    msg[0] = 0x22; // Wheel 2
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.05);

    msg[0] = positions2_low; // 0x01
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.05);

    msg[0] = positions2_high; // 0x01
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.05);

    yCDebug(EWC) << "high byte";
    return true;
}

bool EcroWheelController::stopMovement()
{
    yCDebug(EWC) << "stopMovement";

    char msg[1];

    msg[0] = 0x32; // invert motor 1
    serial->send(msg, 1);
    yarp::os::SystemClock::delaySystem(0.5);

    msg[0] = {0x28};
    serial->send(msg, 1); // wste ambos, 29 limpiaria 1, 30 el 2?
    yarp::os::SystemClock::delaySystem(0.5);

    return true;
}

//-- Robot camera related functions

bool EcroWheelController::tiltDown(double velocity)
{
    yCDebug(EWC) << "tiltDown" << velocity;
    return true;
}

bool EcroWheelController::panLeft(double value)
{
    yCDebug(EWC) << "panLeft" << value;
    return true;
}

bool EcroWheelController::stopCameraMovement()
{
    yCError(EWC) << "stopCameraMovement not implemented yet";
    return false;
}
