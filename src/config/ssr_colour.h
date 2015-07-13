#ifndef SSR_COLOUR_H
#define SSR_COLOUR_H

/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright © 2015
 * Quality and Usability Lab
 * Berlin Institute of Technology
 * http://www.qu.tu-berlin.de
 *
 * For more detailed information, please read the license.txt in the root directory.
 */

//JUCE Lib
#include <JUCE/JuceHeader.h>

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
