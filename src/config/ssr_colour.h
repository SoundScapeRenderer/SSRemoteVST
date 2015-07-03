#ifndef SSR_COLOUR_H
#define SSR_COLOUR_H

//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

namespace SSR
{

  namespace colour
  {

    enum Colours
    {
      background_grey,
      foreground_grey,
      frame_colour,
      blue,
      purple,
      white,
      black
    };

    juce::Colour get_colour(SSR::colour::Colours specifier);

  }

}

#endif
