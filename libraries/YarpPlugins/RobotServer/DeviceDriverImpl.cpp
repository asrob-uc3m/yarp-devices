// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RobotServer.hpp"

namespace asrob
{

bool RobotServer::open(yarp::os::Searchable& config)
{
    rpcServer.setReader(*this);

    yarp::os::Value *name;
    if (config.check("subdevice",name))
    {
        CD_INFO("Subdevice %s\n", name->toString().c_str());
        if (name->isString())
        {
            // maybe user isn't doing nested configuration
            yarp::os::Property p;
            p.fromString(config.toString());
            p.put("device",name->toString());
            robotDevice.open(p);
        }
        else
            robotDevice.open(*name);
    }
    else
    {
        CD_ERROR("\"--subdevice <name>\" not set in RobotServer\n");
        return false;
    }
    if( ! robotDevice.isValid() )
    {
        CD_ERROR("subdevice <%s> not valid\n", name->toString().c_str());
        return false;
    }
    if( ! robotDevice.view( iRdRobot ) )
    {
        CD_ERROR("iRdRobot view failed\n");
        return false;
    }

    //Look for the portname to register (--name option)
    if (config.check("name",name))
        rpcServer.open(name->asString()+"/rpc:s");
    else
        rpcServer.open("/RobotServer/rpc:s");

    return true;
}

bool RobotServer::close()
{
    rpcServer.close();
    robotDevice.close();
    return true;
}

}  // namespace asrob
