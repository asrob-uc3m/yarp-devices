// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#include "RobotServer.hpp"

#include <yarp/os/LogStream.h>
#include <yarp/os/Property.h>

#include "LogComponent.hpp"

using namespace asrob;

bool RobotServer::open(yarp::os::Searchable& config)
{
    rpcServer.setReader(*this);

    yarp::os::Value *name;

    if (config.check("subdevice", name))
    {
        yCInfo(RS) << "Subdevice" << name->toString();

        if (name->isString())
        {
            // maybe user isn't doing nested configuration
            yarp::os::Property p;
            p.fromString(config.toString());
            p.put("device", name->toString());
            p.setMonitor(config.getMonitor(), name->toString().c_str());
            robotDevice.open(p);
        }
        else
        {
            robotDevice.open(*name);
        }
    }
    else
    {
        yCError(RS) << "\"--subdevice <name>\" not set in RobotServer";
        return false;
    }

    if (!robotDevice.isValid())
    {
        yCError(RS) << "Subdevice" << name->toString() << "not valid";
        return false;
    }

    if (!robotDevice.view( iRobotManager))
    {
        yCError(RS) << "iRobotManager view failed";
        return false;
    }

    //Look for the portname to register (--name option)
    if (config.check("name", name))
    {
        return rpcServer.open(name->asString() + "/rpc:s");
    }
    else
    {
        return rpcServer.open("/RobotServer/rpc:s");
    }
}

bool RobotServer::close()
{
    rpcServer.close();
    robotDevice.close();
    return true;
}
