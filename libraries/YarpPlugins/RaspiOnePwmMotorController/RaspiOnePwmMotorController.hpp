// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __RASPI_ONE_PWM_MOTOR_CONTROLLER__
#define __RASPI_ONE_PWM_MOTOR_CONTROLLER__

#include <vector>

#include <yarp/dev/DeviceDriver.h>

#include "IRobotManager.hpp"

extern "C" {
#include "pwm.h"
}

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief RaspiOnePwmMotorController
 */
class RaspiOnePwmMotorController : public yarp::dev::DeviceDriver,
                                   public IRobotManager
{
public:
    // -------- RobotManager declarations. Implementation in RaspiOnePwmMotorController.cpp --------

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
    /** Check if index is within range (referred to driver vector size).
     * @param idx index to check.
     * @return true/false on success/failure.
     */
    bool indexWithinRange(const int& idx);

    std::vector<int> gpios;
};

} // namespace asrob

#endif // __RASPI_ONE_PWM_MOTOR_CONTROLLER__
