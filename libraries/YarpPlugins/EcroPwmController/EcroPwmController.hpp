// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __ECRO_PWM_CONTROLLER__
#define __ECRO_PWM_CONTROLLER__

#include <yarp/dev/DeviceDriver.h>
#include <yarp/dev/ISerialDevice.h>
#include <yarp/dev/PolyDriver.h>

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
    bool sendCurrentJointValues();

    yarp::dev::PolyDriver serialDevice;
    yarp::dev::ISerialDevice * serial;

    int leftMotorVelocity {0};
    int rightMotorVelocity {0};
};

} // namespace asrob

#endif // __ECRO_PWM_CONTROLLER__
