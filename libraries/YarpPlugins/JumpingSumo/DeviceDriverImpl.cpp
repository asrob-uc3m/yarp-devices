#include "JumpingSumo.hpp"

#include <string>
#include <ColorDebug.hpp>

using namespace asrob;

bool JumpingSumo::open(yarp::os::Searchable& config)
{
    bool failed = false;

    eARCONTROLLER_ERROR error = ARCONTROLLER_OK;
    eARDISCOVERY_ERROR errorDiscovery = ARDISCOVERY_OK;
    eARCONTROLLER_DEVICE_STATE deviceState = ARCONTROLLER_DEVICE_STATE_MAX;

    ARSAL_Sem_Init(&stateSem, 0, 0);

    device = ARDISCOVERY_Device_New(&errorDiscovery);

    if (errorDiscovery != ARDISCOVERY_OK)
    {
        CD_WARNING("unable to create discovery device: %s\n", ARDISCOVERY_Error_ToString(errorDiscovery));
        failed = true;
    }
    else
    {
        CD_INFO("created discovery device\n");

        errorDiscovery = ARDISCOVERY_Device_InitWifi(device, ARDISCOVERY_PRODUCT_JS, JS_DEVICE_NAME, JS_IP_ADDRESS, JS_DISCOVERY_PORT);

        if (errorDiscovery != ARDISCOVERY_OK)
        {
            CD_WARNING("unable to initialize wifi: %s\n", ARDISCOVERY_Error_ToString(errorDiscovery));
            failed = true;
        }
        else
        {
            CD_INFO("wifi initialized\n");
        }
    }

    if (!failed)
    {
        deviceController = ARCONTROLLER_Device_New(device, &error);

        if (error != ARCONTROLLER_OK)
        {
            CD_WARNING("unable to create device controller: %s\n", ARCONTROLLER_Error_ToString(error));
            failed = true;
        }
        else
        {
            CD_INFO("created controller device\n");
            ARDISCOVERY_Device_Delete(&device);
        }
    }

    if (!failed)
    {
        error = ARCONTROLLER_Device_AddStateChangedCallback(deviceController, stateChanged, &stateSem);

        if (error != ARCONTROLLER_OK)
        {
            CD_WARNING("unable to add state-changed callback: %s\n", ARCONTROLLER_Error_ToString(error));
            failed = true;
        }
        else
        {
            CD_INFO("added state-changed callback\n");
        }
    }

    if (!failed)
    {
        error = ARCONTROLLER_Device_AddCommandReceivedCallback(deviceController, commandReceived, deviceController);

        if (error != ARCONTROLLER_OK)
        {
            CD_WARNING("unable to add command-received callback: %s\n", ARCONTROLLER_Error_ToString(error));
            failed = true;
        }
        else
        {
            CD_INFO("added command-received callback\n");
        }
    }

    if (!failed)
    {
        error = ARCONTROLLER_Device_SetVideoStreamCallbacks(deviceController, decoderConfig, didReceiveFrame, NULL, &imageBuffer);

        if (error != ARCONTROLLER_OK)
        {
            CD_WARNING("unable to set video stream callback: %s\n", ARCONTROLLER_Error_ToString(error));
            failed = true;
        }
        else
        {
            CD_INFO("set video stream callback\n");
        }
    }

    if (!failed)
    {
        error = ARCONTROLLER_Device_Start(deviceController);

        if (error != ARCONTROLLER_OK)
        {
            CD_WARNING("uUnable to start device: %s\n", ARCONTROLLER_Error_ToString(error));
            failed = true;
        }
        else
        {
            CD_INFO("device started\n");
        }
    }

    if (!failed)
    {
        ARSAL_Sem_Wait(&stateSem);

        deviceState = ARCONTROLLER_Device_GetState(deviceController, &error);

        if (error != ARCONTROLLER_OK || deviceState != ARCONTROLLER_DEVICE_STATE_RUNNING)
        {
            CD_WARNING("unable to get device state or device not running: %d, %s\n", deviceState, ARCONTROLLER_Error_ToString(error));
            failed = true;
        }
        else
        {
            CD_INFO("device up and running\n");
        }
    }

    if (!failed)
    {
        error = ARCONTROLLER_Device_StartVideoStream(deviceController);

        if (error != ARCONTROLLER_OK)
        {
            CD_WARNING("unable to start vide stream: %s\n", ARCONTROLLER_Error_ToString(error));
            failed = true;
        }
        else
        {
            CD_INFO("started video stream\n");
        }
    }

    if (!failed)
    {
        error = deviceController->jumpingSumo->sendMediaStreamingVideoEnable(deviceController->jumpingSumo, 1);

        if (error != ARCONTROLLER_OK)
        {
            CD_WARNING("unable to enable video streaming: %s\n", ARCONTROLLER_Error_ToString(error));
            failed = true;
        }
        else
        {
            CD_INFO("video streaming enabled\n");
        }
    }

    if (!failed)
    {
        std::string portName;

        if (config.check("name"))
        {
            portName = config.find("name").asString();
        }
        else
        {
            portName = "/";
            portName += config.find("device").asString();
        }

        portName += "/img:o";

        if (!imagePort.open(portName.c_str()))
        {
            CD_WARNING("unable to open port \"%s\"\n", portName.c_str());
            failed = true;
        }
        else
        {
            CD_INFO("opened port \"%s\"\n", portName.c_str());
            imageBuffer.attach(imagePort);
        }
    }

    if (!failed)
    {
        CD_SUCCESS("configured and ready\n");
        return true;
    }
    else
    {
        CD_ERROR("errors occurred\n");
        return false;
    }
}

bool JumpingSumo::close()
{
    imageBuffer.detach();
    imagePort.close();

    eARCONTROLLER_ERROR error = ARCONTROLLER_OK;
    eARCONTROLLER_DEVICE_STATE deviceState = ARCONTROLLER_DEVICE_STATE_MAX;

    if (deviceController != NULL)
    {
        deviceState = ARCONTROLLER_Device_GetState(deviceController, &error);

        if (error == ARCONTROLLER_OK && deviceState != ARCONTROLLER_DEVICE_STATE_STOPPED)
        {
            CD_INFO("disconnecting...\n");

            if (ARCONTROLLER_Device_Stop(deviceController) == ARCONTROLLER_OK)
            {
                ARSAL_Sem_Wait(&stateSem);
            }
        }
        else if (error != ARCONTROLLER_OK)
        {
            CD_WARNING("unable to get device state: %s\n", ARCONTROLLER_Error_ToString(error));
        }

        CD_INFO("deleting device controller...\n");

        ARCONTROLLER_Device_Delete(&deviceController);
    }

    ARSAL_Sem_Destroy(&stateSem);

    return true;
}
