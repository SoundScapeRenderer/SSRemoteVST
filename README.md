# SSRemote VST

This VST Plugin addresses the need for the automation of [SoundScapeRenderer (SSR)](http://spatialaudio.net/ssr/) scenes from a [Digital Audio Workstation (DAW)](https://en.wikipedia.org/wiki/Digital_audio_workstation).

## Description of the GUI

The VST Plugins GUI is generally splitted in two sections. The <b>General Controls</b> section and the <b>Source Controls</b> section. 

### General Controls

|Name       |GUI Element|Description|
|:---------:|:---------:|:---------:|
|Connect    |Button     |connects or disconnects the connection to the SSR|
|New Source |Button     |creates a new source with default values for the parameters|

### Source Controls

|Name       |GUI Element|Description|
|:---------:|:---------:|:---------:|
|Source     |Dropdown   |select a source for manipulation|
|Name       |Textfield  |read and writeable textfield for the name of the source|
|Jackport   |Dropdown   |select the jackport the source shall connect to|
|Model      |Dropdown   |select the type of model of the source|
|Azimuth    |Textfield  |readable only textfield for displaying the sources orientation|
|Mute       |Button     |mutes and unmutes the source|
|Fix        |Button     |fix and unfix the source position|
|Gain       |Slider     |adjust the gain of the source in dB|
|Source Control Pad|2D Pad|displayes the sources position|
|Zoom       |Buttons    |zooms in and out the Source Control Pad|
|Scale Reference|-      |displays a scale reference in meter for the Source Control Pad|
|X Position |Slider     |controller for the X position of the source|
|Y Position |Slider     |controller for the Y position of the source|

## Automatable Parameters

The Host (DAW) is able to automate the following parameters:

+ X Position
+ Y Position
+ Gain
+ Mute
+ Model
+ Fixed

## Logfiles

All logs of the Plugin will be written in the ```log.txt``` in the root directory and will look as follows:

```
[YYYY-MM-DD HH:mm:SS] [<LOGTYPE>] <Log text>
```

## License

[GNU GENERAL PUBLIC LICENSE](http://www.gnu.org/licenses/gpl-3.0.de.html)<br/>
Version 3, 29 June 2007

Copyright © 2015<br/>
Quality and Usability Lab<br7/>
Berlin Institute of Technology<br/>
http://www.qu.tu-berlin.de/<br/>

For more detailed information, please read the license.txt in the root directory.

# Installation

## Config File

The VST Plugin requires a config file to successfully establish a TCP/IP connection to the SSR. The user has to create a file called <b>ssremote_config.xml</b> with the following content: 

```XML
<?xml version="1.0" encoding="utf-8"?>
<config>
  <network>
    <host>localhost</host>
    <port>4711</port>
    <timeout>1000</timeout>
  </network>
</config>
```

| Markup | Description |
| ------:|:------------|
|network|the network configuration|
|host   |the host on which the SSR is running|
|port   |the port on which the SSR is listening for incoming TCP/IP requests|
|timeout|the time in milliseconds the VST Plugin waits for an answer by the SSR|

The contents of the markups host, port and timeout are just examples which the user may edit regarding his systems and SSR configuration.

## Environment Variables

Please set the following environment variables described as follows:

The folder where your VST3 SDK (Steinberg) is located in your file system:

```bash
export VST3_SDK=/path/to/VST3SDK
```

The folder where the SSRemote VST is located in your file system:

```bash
export SSREMOTE_VST=/path/to/ssremote_vst
```

The folder where the JUCE library code is located in the SSRemote VST folder (due to the fact, that the JUCE library includes ```"AppConfig.h"``` for example, this environment variable has to be set as described!):

```bash
export JUCE_LIB_CODE=/path/to/ssremote_vst/JUCE
```

## Dependencies

The Plugin uses the [C++11 Standard](https://en.wikipedia.org/wiki/C%2B%2B11) which has to be supported by your compiler (e.g. at least GCC 4.7).

The following libraries are used:

+ Steinberg VST
+ JUCE (currently located in the repository)
+ Boost C++ Library
+ Jack-Audio-Connection-Kit
