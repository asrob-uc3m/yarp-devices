import yarp.*;
import asrob_yarp_devices.*;

class ExampleRobotClient {
    public static void main(String[] args) {
        System.out.println("Hey");
        System.loadLibrary("yarp_java");
        System.loadLibrary("jasrob_yarp_devices");
        //AsrobYarpDevicesLoader.load();

        Network.init();

        if (!Network.checkNetwork()) {
            System.out.println("[error] Please try running yarp server");
            System.exit(-1);
        }

        Property robotOptions = new Property();
        robotOptions.put("device","RobotClient");
        robotOptions.put("name","/ecroSim");

        PolyDriver robotDevice = new PolyDriver(robotOptions); // calls open -> connects
        IRobotManager robot = asrob_yarp_devices.viewIRobotManager(robotOptions); // view the actual interface

        System.out.println("moveForward");
        robot.moveForward(1);

        System.out.println("delay(5)");
        Time.delay(5); // delay in [seconds]

        System.out.println("stopMovement");
        robot.stopMovement();
    }
}
