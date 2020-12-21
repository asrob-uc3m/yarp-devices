// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __RASPI_TWO_PWM_MOTOR_CONTROLLER__
#define __RASPI_TWO_PWM_MOTOR_CONTROLLER__

#include <yarp/os/all.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/Drivers.h>
#include <yarp/dev/PolyDriver.h>

#include <vector>

#include "IRobotManager.hpp"

#include <wiringPi.h>

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief RaspiTwoPwmMotorController
 */
class RaspiTwoPwmMotorController : public yarp::dev::DeviceDriver, public IRobotManager {

public:

    RaspiTwoPwmMotorController() {}

    // -------- RobotManager declarations. Implementation in RaspiTwoPwmMotorController.cpp --------

    //-- Robot movement related functions
    virtual bool moveForward(double value);
    virtual bool turnLeft(double value);
    virtual bool stopMovement();

    //-- Robot camera related functions
    virtual bool tiltDown(double value);
    virtual bool panLeft(double value);
    virtual bool stopCameraMovement();

    // -------- DeviceDriver declarations. Implementation in DeviceDriverImpl.cpp --------

    /**
    * Open the DeviceDriver.
    * @param config is a list of parameters for the device.
    * Which parameters are effective for your device can vary.
    * See \ref dev_examples "device invocation examples".
    * If there is no example for your device,
    * you can run the "yarpdev" program with the verbose flag
    * set to probe what parameters the device is checking.
    * If that fails too,
    * you'll need to read the source code (please nag one of the
    * yarp developers to add documentation for your device).
    * @return true/false upon success/failure
    */
    virtual bool open(yarp::os::Searchable& config);

    /**
    * Close the DeviceDriver.
    * @return true/false on success/failure.
    */
    virtual bool close();

    // ------------------------------- Private -------------------------------------

private:

    /** Check if index is within range (referred to driver vector size).
     * @param idx index to check.
     * @return true/false on success/failure.
     */
    bool indexWithinRange(const int& idx);

    std::vector< int > gpios;

    static const int LEFT_MOTOR_IN1;
    static const int LEFT_MOTOR_IN2;
    static const int RIGHT_MOTOR_IN1;
    static const int RIGHT_MOTOR_IN2;
};

} // namespace asrob

#endif // __RASPI_TWO_PWM_MOTOR_CONTROLLER__
