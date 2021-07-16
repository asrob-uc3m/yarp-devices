// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __ECRO_PWM_CONTROLLER__
#define __ECRO_PWM_CONTROLLER__

#include <yarp/dev/DeviceDriver.h>

#include <SerialStream.h>

#include "IRobotManager.hpp"

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief EcroPwmController
 */
class EcroPwmController : public yarp::dev::DeprecatedDeviceDriver,
                          public IRobotManager
{
public:
    // -------- RobotManager declarations. Implementation in EcroPwmController.cpp --------

    //-- Robot movement related functions
    bool moveForward(double value) override;
    bool turnLeft(double value) override;
    bool stopMovement() override;

    //-- Robot camera related functions
    bool tiltDown(double value) override;
    bool panLeft(double value) override;
    bool stopCameraMovement() override;

    // -------- DeviceDriver declarations. Implementation in DeviceDriverImpl.cpp --------
    bool open(yarp::os::Searchable& config) override;
    bool close() override;

private:
    SerialPort * serialPort;
    bool sendCurrentJointValues();

    int leftMotorVelocity;
    int rightMotorVelocity;

    static const int leftMotorRangeMin = 0;
    static const int leftMotorRangeMax = 90;
    static const int leftMotorInitial = 0;

    static const int rightMotorRangeMin = 0;
    static const int rightMotorRangeMax = 90;
    static const int rightMotorInitial = 0;

    static const int leftMotorOffset = 90;
    static const int rightMotorOffset = 90;
};

} // namespace asrob

#endif // __ECRO_PWM_CONTROLLER__
