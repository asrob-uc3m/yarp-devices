// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __FAKE_MOTOR_CONTROLLER__
#define __FAKE_MOTOR_CONTROLLER__

#include <yarp/dev/DeviceDriver.h>

#include "IRobotManager.hpp"

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief FakeMotorController
 */
class FakeMotorController : public yarp::dev::DeviceDriver,
                            public IRobotManager
{
public:
    // -------- RobotManager declarations. Implementation in FakeMotorController.cpp --------
    bool moveForward(double value) override;
    bool turnLeft(double value) override;
    bool stopMovement() override;
    bool tiltDown(double value) override;
    bool panLeft(double value) override;
    bool stopCameraMovement() override;

    // -------- DeviceDriver declarations. Implementation in DeviceDriverImpl.cpp --------
    bool open(yarp::os::Searchable& config) override;
    bool close() override;
};

} // namespace asrob

#endif // __FAKE_MOTOR_CONTROLLER__
