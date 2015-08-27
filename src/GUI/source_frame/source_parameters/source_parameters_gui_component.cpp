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

#include <src/GUI/source_frame/source_parameters/source_parameters_gui_component.h>

//C++ Libs
#include <string>
#include <map>
#include <algorithm>

//Own Libs
#include <src/GUI/gui_components_configurator.h>
#include <src/config/ssr_colour.h>
#include <src/controller.h>
#include <src/utils/logger.h>

SSR::Source_parameters_gui_component::Source_parameters_gui_component(Controller* controller)
: AudioProcessorEditor(controller)
, name_text_editor_is_changing(false)
, source_orientation_text_editor_is_changing(false)
, id_text_editor_is_changing(false)
, properties_file_text_editor_is_changing(false)
, fixed_button(new juce::TextButton("fixed_button"))
, mute_button(new juce::TextButton("mute_button"))
, source_label(new juce::Label("id_label", TRANS("Source")))
, sources_dropwdown(new juce::ComboBox("sources_dropwdown"))
, name_label(new juce::Label("name_label", TRANS("Name")))
, name_text_editor(new juce::TextEditor("name_text_editor"))
, orientation_label(new juce::Label("orientation_label", TRANS("Azimuth")))
, orientation_text_editor(new juce::TextEditor("orientation_text_editor"))
, jackport_label(new juce::Label("jackport_label", TRANS("Jackport")))
, jackport_dropdown(new juce::ComboBox("jackport_dropdown"))
, gain_slider(new juce::Slider("gain_slider"))
, gain_label(new juce::Label("gain_label", TRANS("Gain")))
, model_label(new juce::Label("model_label", TRANS("Model")))
, model_dropdown(new juce::ComboBox("model_dropdown"))
{
  make_all_visible();
  configure_all_components();
  fill_jackport_dropdown();
  set_bounds();
  setSize(450, 400);
}

SSR::Source_parameters_gui_component::~Source_parameters_gui_component()
{
  removeAllChildren();
}

void SSR::Source_parameters_gui_component::buttonClicked(juce::Button* buttonThatWasClicked)
{

  if (buttonThatWasClicked == mute_button.get()) {
      getProcessor()->set_parameter_source_mute(mute_button->getToggleState());
  } else if (buttonThatWasClicked == fixed_button.get()) {
      getProcessor()->set_parameter_source_fixed(fixed_button->getToggleState());
  }

}

void SSR::Source_parameters_gui_component::sliderValueChanged(juce::Slider* sliderThatWasMoved)
{

  if (sliderThatWasMoved == gain_slider.get()) {
      getProcessor()->set_parameter_source_gain(gain_slider->getValue(), false);
  }

}

void SSR::Source_parameters_gui_component::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged)
{

  if (comboBoxThatHasChanged == jackport_dropdown.get()) {
      std::string selected_port = jackport_dropdown->getText().toStdString();
      getProcessor()->set_parameter_source_port(selected_port);
  } else if (comboBoxThatHasChanged == model_dropdown.get()) {
      int set_id = model_dropdown->getSelectedId();
      getProcessor()->set_parameter_source_model_point(set_id == 1);
  } else if (comboBoxThatHasChanged == sources_dropwdown.get()) {
      int id = sources_dropwdown->getSelectedId();
      getProcessor()->reset_source(id);
  }

}

void SSR::Source_parameters_gui_component::textEditorReturnKeyPressed(TextEditor& textEditorThatWasChanged)
{

  if (textEditorThatWasChanged == name_text_editor.get()) {
      getProcessor()->set_parameter_source_name(name_text_editor->getText().toStdString());
      name_text_editor_is_changing = false;
  }

}

void SSR::Source_parameters_gui_component::textEditorTextChanged(TextEditor& text_editor_thats_changing)
{

  if (text_editor_thats_changing == name_text_editor.get()) {
      name_text_editor_is_changing = true;
  }

}

void SSR::Source_parameters_gui_component::textEditorFocusLost(TextEditor& text_editor_focus_lost)
{

  if (text_editor_focus_lost == name_text_editor.get()) {
      name_text_editor_is_changing = false;
  }

}

void SSR::Source_parameters_gui_component::set_gain_slider_value(const float value)
{
  gain_slider->setValue(value, juce::dontSendNotification);
}

void SSR::Source_parameters_gui_component::set_model_selected_id(const int id)
{
  model_dropdown->setSelectedId(id, juce::dontSendNotification);
}

void SSR::Source_parameters_gui_component::set_jackport_selected_entry(const std::string& entry)
{

  if (entry != jackport_dropdown->getText()) {

      bool entry_exists = false;

      for (std::map<int, std::string>::iterator it = jackport_dropdown_menu_entries.begin(); it != jackport_dropdown_menu_entries.end(); ++it) {

          if (it->second == entry) {
              entry_exists = true;
              jackport_dropdown->setSelectedId(it->first, juce::dontSendNotification);
          }

      }

      if (!entry_exists) {
          std::string message = "jackport_dropdown_menu entry " + entry + " does not exist in dropdown menu!";
          SSR::Logger::get_instance()->log(SSR::Logger::Level::ERROR, message, LOG_TO_FILE);
      }

  }

}

void SSR::Source_parameters_gui_component::set_mute_button_toggle_state(const bool state)
{
  mute_button->setToggleState(state, juce::dontSendNotification);
}

void SSR::Source_parameters_gui_component::set_fixed_button_toggle_state(const bool state)
{
  fixed_button->setToggleState(state, juce::dontSendNotification);
}

void SSR::Source_parameters_gui_component::set_id_text_editor_text(const juce::String& text)
{
  //TODO: Replace this method
  //set_text_editor_text(*id_text_editor, text, id_text_editor_is_changing);
}

void SSR::Source_parameters_gui_component::set_name_text_editor_text(const juce::String& text)
{
  set_text_editor_text(*name_text_editor, text, name_text_editor_is_changing);
}

void SSR::Source_parameters_gui_component::set_orientation_text_editor_text(const juce::String& text)
{
  set_text_editor_text(*orientation_text_editor, text, false);
}

void SSR::Source_parameters_gui_component::set_text_editor_text(juce::TextEditor& texteditor, const juce::String& text, bool is_changing)
{
  if (!is_changing) {
      texteditor.setText(text, false);
  }
}

void SSR::Source_parameters_gui_component::set_bounds()
{
  int middle_line = 120;
  int standard_width = 138;
  int standard_label_width = 100;
  int standard_heigth = 25;
  int gap_standard = 12;
  int current_y = 0;

  source_label->setBounds(0, current_y, standard_label_width, standard_heigth);
  sources_dropwdown->setBounds(middle_line, 0, standard_width, standard_heigth);
  current_y += standard_heigth + gap_standard;

  name_label->setBounds(0, current_y, standard_label_width, standard_heigth);
  name_text_editor->setBounds(middle_line, current_y, standard_width, standard_heigth);
  current_y += standard_heigth + gap_standard;

  jackport_label->setBounds(0, current_y, standard_label_width, standard_heigth);
  jackport_dropdown->setBounds(middle_line, current_y, standard_width, standard_heigth);
  current_y += standard_heigth + gap_standard;

  model_label->setBounds(0, current_y, standard_label_width, standard_heigth);
  model_dropdown->setBounds(middle_line, current_y, standard_width, standard_heigth);
  current_y += standard_heigth + gap_standard;

  orientation_label->setBounds(0, current_y, standard_label_width, standard_heigth);
  orientation_text_editor->setBounds(middle_line, current_y, standard_width, standard_heigth);
  current_y += standard_heigth + gap_standard;

  mute_button->setBounds(middle_line, current_y, standard_width, standard_heigth);
  current_y += standard_heigth + gap_standard;

  fixed_button->setBounds(middle_line, current_y, standard_width, standard_heigth);
  current_y += standard_heigth + gap_standard;

  gain_label->setBounds(0, current_y, standard_label_width, standard_heigth);
  gain_slider->setBounds(middle_line, current_y, standard_width + 80, standard_heigth);
  current_y += standard_heigth + gap_standard;

}

void SSR::Source_parameters_gui_component::fill_jackport_dropdown()
{
  //Fills the Dropdown with all jack ports
  std::vector<std::string> all_jack_ports = getProcessor()->get_all_jack_ports(JackPortIsOutput);

  jackport_dropdown->clear(juce::dontSendNotification);

  int item_index = 10;
  for (std::vector<std::string>::iterator it = all_jack_ports.begin(); it != all_jack_ports.end(); it++) {

      jackport_dropdown->addItem(String(*it), item_index);
      jackport_dropdown_menu_entries.insert(std::pair<int, std::string>(item_index, *it));
      item_index++;

  }

}

void SSR::Source_parameters_gui_component::configure_all_components()
{
  configure_text_editors();
  configure_text_buttons();
  configure_labels();
  configure_dropdowns();
  configure_sliders();
}

void SSR::Source_parameters_gui_component::configure_text_editors()
{
  SSR::configure_text_editor(*name_text_editor, false, true, 30, juce::String(""), juce::String("Default Source Name"));
  name_text_editor->addListener(this);

  SSR::configure_text_editor(*orientation_text_editor, true, false, 8, juce::String(""), juce::String("0.0"));
  orientation_text_editor->addListener(this);
  orientation_text_editor->setColour(TextEditor::backgroundColourId, SSR::colour::get_colour(SSR::colour::Colours::foreground_grey));
}

void SSR::Source_parameters_gui_component::configure_text_buttons()
{
  SSR::configure_text_button(*fixed_button, juce::String("Fix"));
  fixed_button->addListener(this);

  SSR::configure_text_button(*mute_button, juce::String("Mute"));
  mute_button->addListener(this);
}

void SSR::Source_parameters_gui_component::configure_labels()
{
  juce::Colour background_colour = SSR::colour::get_colour(SSR::colour::Colours::background_grey);

  SSR::configure_label(*source_label,           background_colour);
  SSR::configure_label(*name_label,             background_colour);
  SSR::configure_label(*orientation_label,      background_colour);
  SSR::configure_label(*jackport_label,         background_colour);
  SSR::configure_label(*model_label,            background_colour);
  SSR::configure_label(*gain_label,             background_colour);
}

void SSR::Source_parameters_gui_component::configure_dropdowns()
{
  SSR::configure_dropdown(*jackport_dropdown, juce::String("No Jackports available!"));
  jackport_dropdown->addListener(this);

  SSR::configure_dropdown(*model_dropdown, juce::String("No Model available!"));
  model_dropdown->addItem("point source", 1);
  model_dropdown->addItem("plain wave", 2);
  model_dropdown->addListener(this);

  SSR::configure_dropdown(*sources_dropwdown, juce::String("N/A"));

  reload_source_dropdown();

  sources_dropwdown->addListener(this);

  sources_dropwdown->setSelectedId(1, juce::dontSendNotification);
}

void SSR::Source_parameters_gui_component::configure_sliders()
{
  SSR::configure_slider(*gain_slider, -60.0, 12.0, 0.01, Slider::LinearHorizontal);
  SSR::configure_slider_textbox(*gain_slider, Slider::TextBoxRight, false, 71, 25);
  gain_slider->addListener(this);
}

void SSR::Source_parameters_gui_component::reload_source_dropdown()
{
  Controller* processor = getProcessor();
  std::shared_ptr< std::vector< std::pair<unsigned int, std::string> > > ids_and_names = processor->get_source_ids_and_names();

  sources_dropwdown->clear(juce::dontSendNotification);

  std::for_each(begin(*ids_and_names), end(*ids_and_names), [=](std::pair<unsigned int, std::string> p) {
    sources_dropwdown->addItem(p.second, p.first);
  });

  sources_dropwdown->setSelectedId(processor->get_source().get_id(), juce::dontSendNotification);
}

void SSR::Source_parameters_gui_component::make_all_visible()
{
  addAndMakeVisible(*fixed_button);
  addAndMakeVisible(*mute_button);
  addAndMakeVisible(*source_label);
  addAndMakeVisible(*name_label);
  addAndMakeVisible(*name_text_editor);
  addAndMakeVisible(*orientation_label);
  addAndMakeVisible(*orientation_text_editor);
  addAndMakeVisible(*jackport_label);
  addAndMakeVisible(*jackport_dropdown);
  addAndMakeVisible(*gain_slider);
  addAndMakeVisible(*model_label);
  addAndMakeVisible(*model_dropdown);
  addAndMakeVisible(*sources_dropwdown);
  addAndMakeVisible(*gain_label);
}
