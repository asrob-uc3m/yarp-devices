// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __LASER_TOWER_OF_DEATH_CONTROLLER__
#define __LASER_TOWER_OF_DEATH_CONTROLLER__

#include <yarp/dev/DeviceDriver.h>
#include <SerialStream.h>

#include "IRobotManager.hpp"

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief LaserTowerOfDeathController
 */
class LaserTowerOfDeathController : public yarp::dev::DeviceDriver,
                                    public IRobotManager
{
public:
    // -------- RobotManager declarations. Implementation in LaserTowerOfDeathController.cpp --------

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
