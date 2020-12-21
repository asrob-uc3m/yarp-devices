// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __ROBOT_SERVER__
#define __ROBOT_SERVER__

#include <yarp/os/all.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/Drivers.h>
#include <yarp/dev/PolyDriver.h>

#include <vector>

#include "IRobotManager.hpp"

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief RobotServer
 */
class RobotServer : public yarp::dev::DeviceDriver, public yarp::os::PortReader {

public:

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

    // -------- PortReader declarations. Implementation in RobotServer.cpp --------

    virtual bool read(yarp::os::ConnectionReader& connection);


// ------------------------------- Private -------------------------------------

private:

    yarp::os::RpcServer rpcServer;

    yarp::dev::PolyDriver robotDevice;
    IRobotManager* iRobotManager;

};

} // namespace asrob

#endif // __ROBOT_SERVER__
