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

//Own Libs
#include <src/GUI/head_frame/head_frame_gui_component.h>
#include <src/GUI/head_frame/network_gui_component.h>
#include <src/config/ssr_colour.h>
#include <src/controller.h>

SSR::Head_frame_GUI_component::Head_frame_GUI_component(Controller* processor)
: AudioProcessorEditor(processor)
, network_component(new SSR::Network_gui_component(processor))
, new_source_button(new juce::TextButton("new_source_button"))
{
  addAndMakeVisible(*network_component);
  network_component->setBounds(35, 41, network_component->getWidth(), network_component->getHeight());

  addAndMakeVisible(*new_source_button);
  new_source_button->setBounds(744, 41, 138, 26);

  configure_new_source_button();

  setSize(900, 100);
}

SSR::Head_frame_GUI_component::~Head_frame_GUI_component()
{
  removeAllChildren();
  network_component             = nullptr;
  new_source_button             = nullptr;
}

void SSR::Head_frame_GUI_component::paint(juce::Graphics& graphics)
{
  typedef SSR::colour::Colours colours;

  graphics.fillAll(SSR::colour::get_colour(colours::white));

  graphics.setColour(SSR::colour::get_colour(colours::frame_colour));
  graphics.drawRoundedRectangle(10, 28, 180, 50, 10.0f, 2.0f);

  graphics.setColour(SSR::colour::get_colour(colours::background_grey));
  graphics.fillRoundedRectangle(10, 28, 180, 50, 10.0f);
}

void SSR::Head_frame_GUI_component::buttonClicked(juce::Button* buttonThatWasClicked)
{
  Controller* processor = getProcessor();

  if (buttonThatWasClicked == new_source_button.get()) {
      processor->new_source();
      new_source_button->setToggleState(false, juce::dontSendNotification);
  }

}

bool SSR::Head_frame_GUI_component::get_connected() const
{
  return network_component->get_connected();
}

void SSR::Head_frame_GUI_component::set_connected(const bool new_state)
{
  network_component->set_connected(new_state);
}

void SSR::Head_frame_GUI_component::configure_new_source_button()
{
  new_source_button->setButtonText (TRANS("New Source"));
  new_source_button->addListener(this);
  new_source_button->setColour(TextButton::buttonColourId, SSR::colour::get_colour(SSR::colour::Colours::white));
  new_source_button->setColour(TextButton::textColourOnId, SSR::colour::get_colour(SSR::colour::Colours::white));
  new_source_button->setColour(TextButton::textColourOffId, SSR::colour::get_colour(SSR::colour::Colours::black));
  new_source_button->setClickingTogglesState(true);
  new_source_button->setTriggeredOnMouseDown(true);
}
