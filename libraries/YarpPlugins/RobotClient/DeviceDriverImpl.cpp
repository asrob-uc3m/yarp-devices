// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RobotClient.hpp"

namespace asrob
{

bool RobotClient::open(yarp::os::Searchable& config)
{
    std::string robotName = config.check("name",yarp::os::Value("name"),"robot name").asString();

    std::string local_s("/robotClient");
    local_s += robotName;
    local_s += "/rpc:c";

    rpcClient.open(local_s);  //-- Default should look like "/......./rpc:c"

    std::string remote_s(robotName);
    remote_s += "/rpc:s";

    int tries = 0;
    while(tries++ < 10)
    {
        yarp::os::Network::connect(local_s,remote_s);
        if( rpcClient.getOutputCount() > 0) break;
        CD_DEBUG("Wait to connect to remote robot '%s', try %d...\n",remote_s.c_str(),tries);
        yarp::os::Time::delay(0.5);
    }

    if (tries == 11)
    {
        CD_ERROR("Timeout on connect to remote robot!\n");
        return false;
    }

    CD_SUCCESS("Connected to remote robot.\n");

    return true;
}

bool RobotClient::close()
{
    rpcClient.close();
    return true;
}

}  // namespace asrob
