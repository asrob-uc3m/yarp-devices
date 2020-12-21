// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RobotClient.hpp"

#include <yarp/os/LogStream.h>

namespace asrob
{

bool RobotClient::open(yarp::os::Searchable& config)
{
    std::string robotName = config.check("name", yarp::os::Value("/name"), "robot name").asString();

    std::string local_s("/robotClient");
    local_s += robotName;
    local_s += "/rpc:c";

    rpcClient.open(local_s); //-- Default should look like "/......./rpc:c"

    std::string remote_s(robotName);
    remote_s += "/rpc:s";

    std::string carrier = config.check("carrier", yarp::os::Value(""), "RPC carrier").asString();

    int tries = 0;

    while (tries++ < 10)
    {
        yarp::os::Network::connect(local_s, remote_s, carrier);
        if (rpcClient.getOutputCount() > 0) break;
        yDebug() << "Wait to connect to remote robot" << remote_s << "on try" << tries;
        yarp::os::Time::delay(0.5);
    }

    if (tries == 11)
    {
        yError() << "Timeout on connect to remote robot!";
        return false;
    }

    yInfo() << "Connected to remote robot";

    return true;
}

bool RobotClient::close()
{
    rpcClient.close();
    return true;
}

} // namespace asrob
