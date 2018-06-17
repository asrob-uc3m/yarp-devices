# Installation from Source Code

This repository stores different YARP devices for different actual devices used in different robots. This huge variability in hardware sometimes makes it complicated to track the dependencies for each device you may want to compile and install. 

This guide aims to simplify as much as possible the process of finding out which are the dependencies you actually need to install for the devices you want to use.

## Common dependencies (Ubuntu)

Some dependencies must be installed for all the devices:

- [Install CMake 3.5+](https://github.com/roboticslab-uc3m/installation-guides/blob/master/install-cmake.md)
- [Install YCM 0.8+](https://github.com/roboticslab-uc3m/installation-guides/blob/master/install-ycm.md)
- [Install YARP 2.3.70+](https://github.com/roboticslab-uc3m/installation-guides/blob/master/install-yarp.md)
- [Install color-debug](https://github.com/roboticslab-uc3m/color-debug)

## Installation (Ubuntu)

Once the required dependencies have been installed, the code has to be compiled and installed. Note that you will be prompted for your password upon using `sudo` a couple of times:

```bash
cd  # go home
mkdir -p repos; cd repos  # make $HOME/repos if it doesn't exist; then, enter it
git clone https://github.com/asrob-uc3m/yarp-devices.git  # Download yarp-devices software from the repository
cd yarp-devices; mkdir build; cd build; cmake ..  # Configure the yarp-devices software
make -j$(nproc)  # Compile
sudo make install  # Install :-)
sudo ldconfig
```

Remember to enable the devices you want to compile using `ccmake` instead of `cmake`.

# Install Bindings

## Install Python bindings

Swig is needed in order to build the python bindings. It is normally installed with
```bash
sudo apt update
sudo apt install swig
sudo apt install libpython-dev  # not installed by default on clean distros
```

**Note:** If you are on Ubuntu Trusty (14.04), you have to install swig3.0 instead of swig
```bash
sudo apt install swig3.0
```

Make sure you have installed previously YARP and yarp-devices.
```bash
cd  # go home
cd repos/yarp-devices/bindings
mkdir build && cd build && cmake .. -DCREATE_PYTHON=ON  # Configure the yarp-devices software
make -j$(nproc)  # compile
sudo make install; sudo ldconfig; cd # install and go home
```

## Install MATLAB bindings

The classical way is via Java bindings, which is similar to Python, then setting the `classpath.txt` and `librarypath.txt` files contained within MATLAB. Ref: http://wiki.icub.org/wiki/Calling_yarp_from_Matlab
