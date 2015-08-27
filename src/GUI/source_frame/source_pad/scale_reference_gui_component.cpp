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

#include <src/GUI/source_frame/source_pad/scale_reference_gui_component.h>

//C++ Libs
#include <string>
#include <sstream>
#include <iomanip>

//JUCE Include
#include <JUCE/JuceHeader.h>

SSR::Scale_reference_GUI_component::Scale_reference_GUI_component(unsigned int reference_pixels, double reference_range)
: reference_pixels(reference_pixels)
, reference_range(reference_range)
, reference_bar_size(30.0f)
, current_reference(0.0f)
, oss(new std::ostringstream())
{
  compute_current_reference();

  setSize(100, 12);
}

SSR::Scale_reference_GUI_component::~Scale_reference_GUI_component()
{

}

void SSR::Scale_reference_GUI_component::paint(Graphics& graphics)
{
  graphics.setColour(juce::Colours::black);
  graphics.drawVerticalLine(0, 0, getHeight() - 1);
  graphics.drawVerticalLine(reference_bar_size, 0, getHeight() - 1.0f);
  graphics.drawHorizontalLine(getHeight() - 1, 0, reference_bar_size);

  oss->str();
  (*oss) << std::fixed << std::setprecision(2) << current_reference << " m";

  graphics.drawSingleLineText(oss->str(), reference_bar_size + 5.0f, getHeight() - 1.0f);
}

void SSR::Scale_reference_GUI_component::set_reference_range(const double new_reference_range)
{
  reference_range = new_reference_range;
  compute_current_reference();
  repaint();
}

void SSR::Scale_reference_GUI_component::compute_current_reference()
{
  current_reference = reference_range / reference_pixels * reference_bar_size;
}
