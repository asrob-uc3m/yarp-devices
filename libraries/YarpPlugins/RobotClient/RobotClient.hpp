// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __ROBOT_CLIENT__
#define __ROBOT_CLIENT__

#include <yarp/os/RpcClient.h>
#include <yarp/dev/DeviceDriver.h>

#include "IRobotManager.hpp"

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief RobotClient
 */
class RobotClient : public yarp::dev::DeviceDriver,
                    public IRobotManager
{
public:
    // -------- DeviceDriver declarations. Implementation in DeviceDriverImpl.cpp --------
    bool open(yarp::os::Searchable& config) override;
    bool close() override;

    // -------- Implementation in RobotClient.cpp --------
    bool moveForward(double value) override;
    bool turnLeft(double value) override;
    bool stopMovement() override;
    bool tiltDown(double value) override;
    bool panLeft(double value) override;
    bool stopCameraMovement() override;

private:
    yarp::os::RpcClient rpcClient;
    bool send1vocab1double(int vocab, double value);
    bool send1vocab(int vocab);
};

} // namespace asrob

#endif // __ROBOT_CLIENT__
