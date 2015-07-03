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

#include <src/config/ssr_colour.h>

//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

juce::Colour SSR::colour::get_colour(SSR::colour::Colours specifier)
{
  juce::Colour colour = juce::Colours::black;

  switch (specifier) {

    case SSR::colour::Colours::background_grey:
      colour = juce::Colour(244, 244, 244);
      break;

    case SSR::colour::Colours::foreground_grey:
      colour = juce::Colour(237, 237, 230);
      break;

    case SSR::colour::Colours::frame_colour:
      colour = juce::Colour(200, 200, 200);
      break;

    case SSR::colour::Colours::blue:
      colour = juce::Colour(73, 174, 247);
      break;

    case SSR::colour::Colours::purple:
      colour = juce::Colour(97, 31, 160);
      break;

    case SSR::colour::Colours::white:
      colour = juce::Colours::white;
      break;

    case SSR::colour::Colours::black:
      colour = juce::Colours::black;
      break;

    default:
      break;

  }

  return colour;
}
