#ifndef AAAAAAA
#define AAAAAAA

#include <yarp/dev/PolyDriver.h>
#include <IRobotManager.hpp>

asrob::IRobotManager *viewIRobotManager(yarp::dev::PolyDriver& d)
{
    asrob::IRobotManager *result;
    d.view(result);
    return result;
}

#endif // AAAAAAA
