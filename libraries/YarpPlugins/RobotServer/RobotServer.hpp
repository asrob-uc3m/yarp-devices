// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __ROBOT_SERVER__
#define __ROBOT_SERVER__

#include <yarp/os/RpcServer.h>

#include <yarp/dev/DeviceDriver.h>
#include <yarp/dev/PolyDriver.h>

#include "IRobotManager.hpp"

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief RobotServer
 */
class RobotServer : public yarp::dev::DeviceDriver,
                    public yarp::os::PortReader
{
public:
    // -------- DeviceDriver declarations. Implementation in DeviceDriverImpl.cpp --------
    bool open(yarp::os::Searchable& config) override;
    bool close() override;

    // -------- PortReader declarations. Implementation in RobotServer.cpp --------
    bool read(yarp::os::ConnectionReader& connection) override;

private:
    yarp::os::RpcServer rpcServer;
    yarp::dev::PolyDriver robotDevice;
    IRobotManager* iRobotManager;
};

} // namespace asrob

#endif // __ROBOT_SERVER__
