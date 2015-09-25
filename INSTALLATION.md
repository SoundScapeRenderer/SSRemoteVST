# Installation / Compilation

The following is a installation guide written for Linux Distributions. The system that was used for testing the guide is [Fedora 22](https://start.fedoraproject.org/). It may help you compiling the SSRemote VST but in no case asserts to claim completness.

The Plugin uses the [C++11 Standard](https://en.wikipedia.org/wiki/C%2B%2B11) which has to be supported by your compiler (e.g. at least GCC 4.7). 

1. Clone the VST Plugin repository from Github:

  ```shell
  # HTTPS
  git clone https://github.com/QULab/SSRemoteVST.git

  # SSH
  git clone git@github.com:QULab/SSRemoteVST.git
  ```
2. Install the Steinberg VST SDK
  
  For installing the Steinberg VST SDK checkout the [Steinberg VST SDK Wiki Page](https://github.com/QULab/SSRemoteVST/wiki/Steinberg-VST).

3. Install several dependencies 

  The SSRemote VST Plugin uses several external libraries. The following is a list of possible dependencies you may have to solve befor compiling:

  * Boost Libraries (boost-devel)
  * OpenGL (freeglut-devel)
  * Jack Audio Connection Kit (jack-audio-connection-kit-devel)
  * ALSA Libraries (alsa-lib-devel)
  * freetype Libraries (freetype-devel)
  * X11 Libraries (libX11-devel, libXinerama-devel)

4. Set the environment variables

  Please set the following environment variables described as follows:

  The directory/location of the Steinberg VST3 SDK:
  
  ```bash
  # Steinberg VST3 Audio Plug-Ins SDK
  export VST3_SDK=/path/to/VST3SDK
  ```

  The directory/location of the SSRemote VST:

  ```bash
  # SSRemote VST
  export SSREMOTE_VST=/path/to/ssremote_vst
  ```

  The directory/location of the JUCE Framework located in the SSRemote VST:
  
  ```bash
  # SSRemote VST JUCE Framework
  export JUCE_LIB_CODE=$SSREMOTE_VST/JUCE
  ```

5. Compile the SSRemote VST Plugin

  Go to the folder of the SSRemote VST and compile as follows:

  ```bash
  # go to the SSREmote VST folder
  cd $SSREMOTE_VST

  # go to the linux build folder
  cd builds/linux

  # compile
  make

  # compile multicore
  make -j8
  ```
  
Congratulations! You successfully compiled the SSRemote VST Plugin!