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

    /**
     * Represents the different colours the function get_colour(...) is able
     * to generate:
     *
     * background_grey: The grey colour that is used for the backgrounds.
     * foreground_grey: The grey colour that is used for the foregrounds.
     * frame_colour: The colour that is used for all the frames.
     * blue: Blue colour.
     * purple: Purple colour.
     * white: White colour.
     * black: Black colour.
     *
     * @see get_colour
     */
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

    /**
     * Returns the colour specified by the transferred speifier.
     *
     * @param   specifier       Specifies which colour the function shall return.
     *                          See SSR::colour::Colours for more information.
     *
     * @return  the specified colour.
     *
     * @see SSR::colour::Colours
     *
     * @author Florian Willich
     */
    juce::Colour get_colour(SSR::colour::Colours specifier);

  }

}

#endif
