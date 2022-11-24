// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __ECRO_WHEEL_CONTROLLER__
#define __ECRO_WHEEL_CONTROLLER__

#include <yarp/dev/DeviceDriver.h>
#include <yarp/dev/ISerialDevice.h>
#include <yarp/dev/PolyDriver.h>

#include "IRobotManager.hpp"

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief EcroWheelController
 */
class EcroWheelController : public yarp::dev::DeprecatedDeviceDriver,
                            public IRobotManager
{
public:
    // -------- RobotManager declarations. Implementation in EcroWheelController.cpp --------

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
    bool sendCurrentJointValues(int16_t positions1);

    yarp::dev::PolyDriver serialDevice;
    yarp::dev::ISerialDevice * serial;
};

} // namespace asrob

#endif // __ECRO_WHEEL_CONTROLLER__
