// Authors: see AUTHORS.md at project root.
// CopyPolicy: released under the terms of the LGPLv2.1, see LICENSE at project root.
// URL: https://github.com/asrob-uc3m/yarp-devices

#ifndef __I_ROBOT_MANAGER_HPP__
#define __I_ROBOT_MANAGER_HPP__

#ifndef SWIG_PREPROCESSOR_SHOULD_SKIP_THIS
#define ASROB_VOCAB(a,b,c,d) ((((int)(d))<<24)+(((int)(c))<<16)+(((int)(b))<<8)+((int)(a)))
#endif // SWIG_PREPROCESSOR_SHOULD_SKIP_THIS

#define VOCAB_MOVE_FORWARD ASROB_VOCAB('m','o','v','f')
#define VOCAB_TURN_LEFT ASROB_VOCAB('t','r','n','l')
#define VOCAB_STOP_MOVEMENT ASROB_VOCAB('s','t','p','m')

#define VOCAB_TILT_DOWN ASROB_VOCAB('t','l','t','d')
#define VOCAB_PAN_LEFT ASROB_VOCAB('p','a','n','l')
#define VOCAB_STOP_CAMERA_MOVEMENT ASROB_VOCAB('s','t','p','c')

namespace asrob{

/**
 * @ingroup yarp_devices_libraries
 *
 * \defgroup YarpPlugins
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

        virtual ~IRobotManager() {}
};

}

#endif //-- __I_ROBOT_MANAGER_HPP__
