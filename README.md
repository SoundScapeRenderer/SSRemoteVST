# SSRemote VST

This VST Plugin addresses the need for the automation of [SoundScapeRenderer (SSR)](http://spatialaudio.net/ssr/) scenes from a [Digital Audio Workstation (DAW)](https://en.wikipedia.org/wiki/Digital_audio_workstation).

## License

GNU GENERAL PUBLIC LICENSE
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

The folder where your VST3 SDK (Steinberg) is located your mashine:

```bash
export VST3_SDK=/path/to/VST3SDK
```

The folder where the SSRemote VST is localted on your mashine:

```bash
export SSREMOTE_VST=/path/to/ssremote_vst
```

The folder where the JUCE library code is located in the SSRemote VST folder (due to the fact, that the JUCE library includes ```"AppConfig.h"``` for example, this environment variable has to be set as described!):

```bash
export JUCE_LIB_CODE=/path/to/ssremote_vst/JUCE
```
