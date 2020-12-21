// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __LASER_TOWER_OF_DEATH_CONTROLLER__
#define __LASER_TOWER_OF_DEATH_CONTROLLER__

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
 * @brief LaserTowerOfDeathController
 */
class LaserTowerOfDeathController : public yarp::dev::DeviceDriver, public IRobotManager {

public:

    LaserTowerOfDeathController() {}

    // -------- RobotManager declarations. Implementation in LaserTowerOfDeathController.cpp --------

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
    bool checkConnection();

    int panJointValue;
    int tiltJointValue;

    static const int panRangeMin = 0;
    static const int panRangeMax = 180;
    static const int panInitial = 90;

    static const int tiltRangeMin = 0;
    static const int tiltRangeMax = 180;
    static const int tiltInitial = 90;

};

} // namespace asrob

#endif // __LASER_TOWER_OF_DEATH_CONTROLLER__
