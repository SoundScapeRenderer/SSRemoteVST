# SSRemote VST
This application addresses the need for the automation of SoundScapeRenderer (SSR) scenes. 

## License

GNU GENERAL PUBLIC LICENSE
Version 3, 29 June 2007

Copyright © 2015<br/>
Quality and Usability Lab
Berlin Institute of Technology
http://www.qu.tu-berlin.de/

For more detailed information, please read the license.txt in the root directory.

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