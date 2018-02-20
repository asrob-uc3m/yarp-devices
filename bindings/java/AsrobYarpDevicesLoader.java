//run this to load the asrobYarpDevices library and initialize the network in Java

package asrob_yarp_devices;

public class AsrobYarpDevicesLoader {
    private static boolean asrobYarpDevicesInitialized = false;

    public static boolean isLoaded() {
        return asrobYarpDevicesInitialized;
    }

    public static void load() {
        if (!asrobYarpDevicesInitialized)
        {
            System.loadLibrary("yarp_java");
            System.loadLibrary("jasrob_yarp_devices");
            System.out.println("AsrobYarpDevices library loaded and initialized");
            System.out.flush();
        }
        else
        {
            System.out.println("AsrobYarpDevices library already loaded and initialized, doing nothing");
            System.out.flush();
        }

        asrobYarpDevicesInitialized = true;
    }
}
