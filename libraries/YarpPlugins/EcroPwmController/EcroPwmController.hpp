// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __ECRO_PWM_CONTROLLER__
#define __ECRO_PWM_CONTROLLER__

#include <yarp/os/all.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/Drivers.h>
#include <yarp/dev/PolyDriver.h>

#include <vector>

#include <SerialStream.h>

#include "IRobotManager.hpp"

#define DEFAULT_SERIAL_PORT_NAME "/dev/ttyUSB0"

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief EcroPwmController
 */
class EcroPwmController : public yarp::dev::DeprecatedDeviceDriver, public IRobotManager {

public:

    EcroPwmController() {}

    // -------- RobotManager declarations. Implementation in EcroPwmController.cpp --------

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
