#include "JumpingSumo.hpp"

#include <cstring>
#include <ColorDebug.hpp>

using namespace asrob;

void JumpingSumo::stateChanged(eARCONTROLLER_DEVICE_STATE newState, eARCONTROLLER_ERROR error, void *customData)
{
    ARSAL_Sem_t *stateSem = (ARSAL_Sem_t *)customData;

    switch (newState)
    {
    case ARCONTROLLER_DEVICE_STATE_STOPPED:
    case ARCONTROLLER_DEVICE_STATE_RUNNING:
        ARSAL_Sem_Post(stateSem);
        break;
    default:
        break;
    }
}

void JumpingSumo::commandReceived(eARCONTROLLER_DICTIONARY_KEY commandKey, ARCONTROLLER_DICTIONARY_ELEMENT_t *elementDictionary, void *customData)
{
    // no-op, can be used to query battery status
}

eARCONTROLLER_ERROR JumpingSumo::decoderConfig(ARCONTROLLER_Stream_Codec_t codec, void *customData)
{
    CD_INFO("codec.type: %d\n", codec.type);
    return ARCONTROLLER_OK;
}

eARCONTROLLER_ERROR JumpingSumo::didReceiveFrame(ARCONTROLLER_Frame_t *frame, void *customData)
{
    if (frame != NULL)
    {
        typedef yarp::os::PortWriterBuffer<JSImage> WriterBuffer;
        WriterBuffer *imageBuffer = (WriterBuffer *)customData;
        JSImage &image = imageBuffer->get();
        CD_DEBUG("width: %d, height: %d\n", frame->width, frame->height);
        CD_DEBUG("available: %d, missed: %zu, capacity: %zu, used: %zu\n", frame->available, frame->missed, frame->capacity, frame->used);
        image.resize(frame->width, frame->height);
        std::memcpy(image.getRawImage(), frame->data, sizeof(unsigned char) * image.width() * image.height());
        imageBuffer->write(true);
    }
    else
    {
        CD_WARNING("Frame is null.\n");
    }

    return ARCONTROLLER_OK;
}
