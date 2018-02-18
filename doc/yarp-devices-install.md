# Installation from Source Code

This repository stores different YARP devices for different actual devices used in different robots. This huge variability in hardware sometimes makes it complicated to track the dependencies for each device you may want to compile and install. 

This guide aims to simplify as much as possible the process of finding out which are the dependencies you actually need to install for the devices you want to use.

## Common dependencies (Ubuntu)

Some dependencies must be installed for all the devices (for Debian guides, see [Debian 6.0.10](yarp-devices-install-on-debian-6.md)):

  - [Install CMake](https://github.com/asrob-uc3m/installation-guides/blob/master/install-cmake.md)
  - [Install YARP](https://github.com/asrob-uc3m/installation-guides/blob/master/install-yarp.md)

Additionally, this project depends on YCM to download and build external packages. Although this process is intended to run automatically during the CMake configuration phase, you may still want to install YCM and said packages by yourself. In that respect, refer to [Install YCM](https://github.com/asrob-uc3m/installation-guides/blob/master/install-ycm.md) and to the installation guides of any package listed below:
- [color-debug](https://github.com/asrob-uc3m/color-debug)

## Installation (Ubuntu)

Once the required dependencies have been installed, the code has to be compiled and installed. Note that you will be prompted for your password upon using `sudo` a couple of times:

```bash
cd  # go home
mkdir -p repos; cd repos  # make $HOME/repos if it doesn't exist; then, enter it
git clone https://github.com/asrob-uc3m/yarp-devices.git  # Download yarp-devices software from the repository
cd yarp-devices; mkdir build; cd build; cmake ..  # Configure the yarp-devices software
make  # Compile
sudo make install  # Install :-)
sudo ldconfig
```

Remember to enable the devices you want to compile using `ccmake` instead of `cmake`.

## Useful links

* [yarp-devices usage](yarp-devices-usage.md)
* [yarp-devices tricks](yarp-devices-tricks.md)
