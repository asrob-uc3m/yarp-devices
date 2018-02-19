//run this to load the asrobYarpDevices library and initialize the network in Java

//import yarp.DVector;

class LoadAsrobYarpDevices{
	private static int asrobYarpDevicesInitialized=0;

	public static int isLoaded()
	{ return asrobYarpDevicesInitialized; }

    public LoadAsrobYarpDevices() {
		if (asrobYarpDevicesInitialized==0)
			{
				System.loadLibrary("jasrobYarpDevices");
				System.out.println("AsrobYarpDevices library loaded and initialized");
				System.out.flush();
			}
		else
			{
				System.out.println("AsrobYarpDevices library already loaded and initialized, doing nothing");
				System.out.flush();
			}
			
		asrobYarpDevicesInitialized=1;
    }
}
