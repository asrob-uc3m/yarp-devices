// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __ROBOT_CLIENT__
#define __ROBOT_CLIENT__

#include <yarp/os/all.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/Drivers.h>
#include <yarp/dev/PolyDriver.h>

#include <vector>

#include "IRobotManager.hpp"

#include "ColorDebug.hpp"

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief RobotClient
 */
class RobotClient : public yarp::dev::DeviceDriver, public IRobotManager
{

public:

    RobotClient();

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

    // -------- Implementation in RobotClient.cpp --------

    //-- Robot movement related functions
    virtual bool moveForward(int velocity);
    virtual bool moveBackwards(int velocity);
    virtual bool turnLeft(int velocity);
    virtual bool turnRight(int velocity);
    virtual bool stopMovement();

    //-- Robot camera related functions
    virtual bool tiltUp(int velocity);
    virtual bool tiltDown(int velocity);
    virtual bool panLeft(int velocity);
    virtual bool panRight(int velocity);
    virtual bool stopCameraMovement();

    //-- Robot connection related functions
    virtual bool connect() { return true; }
    virtual bool disconnect() { return true; }
    virtual bool test() { return true; }
    virtual void setEnabled(bool enabled) {}

    virtual void onDestroy() {}

// ------------------------------- Private -------------------------------------

private:

    yarp::os::RpcClient rpcClient;

    bool send1vocab1int(int vocab, int integer);
    bool send1vocab(int vocab);

};

}  // namespace asrob

#endif  // __ROBOT_CLIENT__
