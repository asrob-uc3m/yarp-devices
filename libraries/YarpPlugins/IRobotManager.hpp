// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __I_ROBOT_MANAGER_HPP__
#define __I_ROBOT_MANAGER_HPP__

#include <yarp/conf/version.h>
#include <yarp/os/Vocab.h>

#if YARP_VERSION_MINOR >= 5
constexpr int VOCAB_MOVE_FORWARD = yarp::os::createVocab32('m','o','v','f');
constexpr int VOCAB_TURN_LEFT = yarp::os::createVocab32('t','r','n','l');
constexpr int VOCAB_STOP_MOVEMENT = yarp::os::createVocab32('s','t','p','m');
constexpr int VOCAB_TILT_DOWN = yarp::os::createVocab32('t','l','t','d');
constexpr int VOCAB_PAN_LEFT = yarp::os::createVocab32('p','a','n','l');
constexpr int VOCAB_STOP_CAMERA_MOVEMENT = yarp::os::createVocab32('s','t','p','c');
#else
constexpr int VOCAB_MOVE_FORWARD = yarp::os::createVocab('m','o','v','f');
constexpr int VOCAB_TURN_LEFT = yarp::os::createVocab('t','r','n','l');
constexpr int VOCAB_STOP_MOVEMENT = yarp::os::createVocab('s','t','p','m');
constexpr int VOCAB_TILT_DOWN = yarp::os::createVocab('t','l','t','d');
constexpr int VOCAB_PAN_LEFT = yarp::os::createVocab('p','a','n','l');
constexpr int VOCAB_STOP_CAMERA_MOVEMENT = yarp::os::createVocab('s','t','p','c');
#endif

namespace asrob
{

/**
 * @ingroup yarp_devices_libraries
 *
 * @defgroup YarpPlugins
 *
  * @brief Base class for Robot Managers. Original copy of this file at https://github.com/asrob-uc3m/yarp-devices/blob/develop/libraries/YarpPlugins/IRobotManager.hpp
 */
class IRobotManager
{
public:
    /// @brief Robot: Move forward (use negative value for move backward). position mode [m]. Velocity mode [m/s].
    virtual bool moveForward(double value) = 0;

    /// @brief Robot: Turn left (use negative value for turn left). position mode [deg]. Velocity mode [deg/s].
    virtual bool turnLeft(double value) = 0;

    /// @brief Robot: Stop movement.
    virtual bool stopMovement() = 0;

    /// @brief Robot camera: Tilt down (use negative value for tilt up). position mode [deg]. Velocity mode [deg/s].
    virtual bool tiltDown(double value) = 0;

    /// @brief Robot camera: Pan left (use negative value for pan right). position mode [deg]. Velocity mode [deg/s].
    virtual bool panLeft(double value) = 0;

    /// @brief Robot camera: Stop movement.
    virtual bool stopCameraMovement() = 0;

    virtual ~IRobotManager() = default;
};

}

#endif // __I_ROBOT_MANAGER_HPP__
