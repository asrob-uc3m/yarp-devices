#! /usr/bin/env python

import yarp
import asrob_yarp_devices

yarp.Network.init()

if yarp.Network.checkNetwork() != True:
    print "[error] Please try running yarp server"
    quit()

robotOptions = yarp.Property()
robotOptions.put('device','RobotClient')
robotOptions.put('name','/ecroSim')
robotDevice = yarp.PolyDriver(robotOptions)  # calls open -> connects

robot = asrob_yarp_devices.viewIRobotManager(robotDevice)  # view the actual interface

print "moveForward"
robot.moveForward(1)

print "delay(5)"
yarp.Time.delay(5)

print "moveForward"
robot.stopMovement()

