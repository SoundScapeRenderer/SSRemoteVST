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

#include <memory>

//Own Libs
#include <src/GUI/source_frame/source_frame_gui_component.h>
#include <src/GUI/source_frame/source_pad/source_pad_and_controls_gui_component.h>
#include <src/GUI/source_frame/source_parameters/source_parameters_gui_component.h>
#include <src/config/ssr_colour.h>
#include <src/utils/helper.h>

SSR::Source_frame_gui_component::Source_frame_gui_component(Controller* controller)
: AudioProcessorEditor(controller)
, source_pad_and_controls(new SSR::Source_pad_and_controls_gui_component(controller))
, source_parameters(new SSR::Source_parameters_gui_component(controller))
, ssr_image_component(new juce::ImageComponent())
, ssr_image(new juce::Image(juce::ImageFileFormat::loadFrom(juce::File(SSR::helper::get_environment_variable("SSREMOTE_VST") + "/Source/images/ssr_logo_large.png"))))
{
  addAndMakeVisible(*source_parameters);
  source_parameters->setBounds(25, 50, source_parameters->getWidth(), source_parameters->getHeight());

  addAndMakeVisible(*source_pad_and_controls);
  source_pad_and_controls->setBounds(394, 50, source_pad_and_controls->getWidth(), source_pad_and_controls->getHeight());

  addAndMakeVisible(*ssr_image_component);
  ssr_image_component->setBounds(32, 414, 84, 58);
  ssr_image_component->setImage(*ssr_image);

  //All addAndMakeVisible objects have to be initialised before here!!
  setSize(900, 500);
}

SSR::Source_frame_gui_component::~Source_frame_gui_component()
{
  removeAllChildren();
}

void SSR::Source_frame_gui_component::paint(juce::Graphics& graphics)
{
  graphics.fillAll(SSR::colour::get_colour(SSR::colour::Colours::white));

  graphics.setColour(SSR::colour::get_colour(SSR::colour::Colours::frame_colour));
  graphics.drawRoundedRectangle(10, 10, getWidth() - 20, getHeight() - 20, 10.0f, 2.0f);

  graphics.setColour(SSR::colour::get_colour(SSR::colour::Colours::background_grey));
  graphics.fillRoundedRectangle(10, 10, getWidth() - 20, getHeight() - 20, 10.0f);
}

void SSR::Source_frame_gui_component::move_source(const float x, const float y)
{
  source_pad_and_controls->move_source(x, y);
}

void SSR::Source_frame_gui_component::set_x_axis_slider_value(const double value)
{
  source_pad_and_controls->set_x_axis_slider_value(value);
}

void SSR::Source_frame_gui_component::set_y_axis_slider_value(const double value)
{
  source_pad_and_controls->set_y_axis_slider_value(value);
}

void SSR::Source_frame_gui_component::set_gain_slider_value(const float value)
{
  source_parameters->set_gain_slider_value(value);
}

void SSR::Source_frame_gui_component::set_model_selected_id(const int id)
{
  source_parameters->set_model_selected_id(id);
}

void SSR::Source_frame_gui_component::set_jackport_selected_entry(const std::string& entry)
{
  source_parameters->set_jackport_selected_entry(entry);
}

void SSR::Source_frame_gui_component::set_mute_button_toggle_state(const bool state)
{
  source_parameters->set_mute_button_toggle_state(state);
}

void SSR::Source_frame_gui_component::set_fixed_button_toggle_state(const bool state)
{
  source_parameters->set_fixed_button_toggle_state(state);
}

void SSR::Source_frame_gui_component::set_id_text_editor_text(const juce::String& text)
{
  source_parameters->set_id_text_editor_text(text);
}

void SSR::Source_frame_gui_component::set_name_text_editor_text(const juce::String& text)
{
  source_parameters->set_name_text_editor_text(text);
}

void SSR::Source_frame_gui_component::set_orientation_text_editor_text(const juce::String& text)
{
  source_parameters->set_orientation_text_editor_text(text);
}

void SSR::Source_frame_gui_component::reload_source_dropdown()
{
  source_parameters->reload_source_dropdown();
}
