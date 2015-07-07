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

#include <src/GUI/source_frame/source_pad/zoom_gui_component.h>

//JUCE Lib
#include <src/JuceHeader.h>

//C++ Lib
#include <cmath>

//Own Libs
#include <src/GUI/gui_components_configurator.h>

SSR::Zoom_GUI_component::Zoom_GUI_component()
: zoom_in_button(new juce::TextButton("zoom_in_button"))
, zoom_out_button(new juce::TextButton("zoom_out_button"))
, zoom_factor(3)
, current_range(10)
{
  addAndMakeVisible(*zoom_in_button);
  zoom_in_button->setBounds(0, 0, 25, 25);
  zoom_in_button->setToggleState(false, juce::sendNotificationAsync);
  zoom_in_button->setClickingTogglesState(false);
  zoom_in_button->addListener(this);
  SSR::configure_text_button(*zoom_in_button, "+");

  addAndMakeVisible(*zoom_out_button);
  zoom_out_button->setBounds(0, 25, 25, 25);
  zoom_out_button->setToggleState(false, juce::sendNotificationAsync);
  zoom_out_button->setClickingTogglesState(false);
  zoom_out_button->addListener(this);
  SSR::configure_text_button(*zoom_out_button, "-");

  setSize(25, 50);
}

SSR::Zoom_GUI_component::~Zoom_GUI_component()
{
  removeAllChildren();
  zoom_in_button                = nullptr;
  zoom_out_button               = nullptr;
}

void SSR::Zoom_GUI_component::buttonClicked(juce::Button* textButton)
{

  if (textButton == zoom_in_button.get()) {
      zoom_factor = zoom_factor >= 1 ? zoom_factor - 1 : 0;
  } else if (textButton == zoom_out_button.get()) {
      zoom_factor = zoom_factor < 9 ? zoom_factor + 1 : 9;
  }

  current_range = look_up_range(zoom_factor);

  sendChangeMessage();
}

double SSR::Zoom_GUI_component::get_current_range() const
{
  return current_range;
}

double SSR::Zoom_GUI_component::look_up_range(const unsigned int zoom_factor)
{
  unsigned int index = zoom_factor < 10 && zoom_factor >= 0 ? zoom_factor : 0;

  std::array<double, 10> look_up_array { 0.4, 1, 3, 5, 10, 20, 50, 200, 500, 2000 };

  return look_up_array[index];
}
