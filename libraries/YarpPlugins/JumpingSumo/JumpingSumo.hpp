#ifndef __JUMPING_SUMO__
#define __JUMPING_SUMO__

#include <yarp/os/Port.h>
#include <yarp/os/PortWriterBuffer.h>
#include <yarp/dev/Drivers.h>
#include <yarp/sig/Image.h>

extern "C" {
#include <libARSAL/ARSAL.h>
#include <libARController/ARController.h>
#include <libARDiscovery/ARDiscovery.h>
}

#include "IRobotManager.hpp"

#define JS_DEVICE_NAME "JS"
#define JS_IP_ADDRESS "192.168.2.1"
#define JS_DISCOVERY_PORT 44444

namespace asrob
{

/**
 * @ingroup YarpPlugins
 * @brief JumpingSumo
 */
class JumpingSumo : public yarp::dev::DeviceDriver,
                    public IRobotManager
{
public:
    JumpingSumo() : device(NULL),
                    deviceController(NULL),
                    stateSem(NULL)
    {}

    // DeviceDriver
    virtual bool open(yarp::os::Searchable& config);
    virtual bool close();

    // IRobotManager
    virtual bool moveForward(double velocity);
    virtual bool turnLeft(double velocity);
    virtual bool stopMovement();
    virtual bool tiltDown(double velocity);
    virtual bool panLeft(double velocity);
    virtual bool stopCameraMovement();

private:
    static void stateChanged(eARCONTROLLER_DEVICE_STATE newState, eARCONTROLLER_ERROR error, void *customData);
    static void commandReceived(eARCONTROLLER_DICTIONARY_KEY commandKey, ARCONTROLLER_DICTIONARY_ELEMENT_t *elementDictionary, void *customData);

    static eARCONTROLLER_ERROR decoderConfig(ARCONTROLLER_Stream_Codec_t codec, void *customData);
    static eARCONTROLLER_ERROR didReceiveFrame(ARCONTROLLER_Frame_t *frame, void *customData);

    ARDISCOVERY_Device_t *device;
    ARCONTROLLER_Device_t *deviceController;
    ARSAL_Sem_t stateSem;

    typedef yarp::sig::ImageOf<yarp::sig::PixelRgb> JSImage;
    yarp::os::Port imagePort;
    yarp::os::PortWriterBuffer<JSImage> imageBuffer;
};

} // namespace asrob

#endif // __JUMPING_SUMO__
