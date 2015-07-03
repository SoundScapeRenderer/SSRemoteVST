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

#include <src/GUI/main_gui_component.h>

//C++ Libs
#include <cmath>
#include <string>
#include <map>
#include <exception>

//Jack Libs
#include <jack/types.h>

//Own Libs
#include <src/utils/jack_client.h>
#include <src/utils/helper.h>
#include <src/utils/debug.h>
#include <src/parameter/parameter.h>
#include <src/GUI/source_frame/source_frame_gui_component.h>
#include <src/GUI/head_frame/head_frame_gui_component.h>
#include <src/config/ssr_colour.h>

Main_GUI_component::Main_GUI_component(Controller* ownerFilter) 
: AudioProcessorEditor(ownerFilter)
, head_frame(new SSR::Head_frame_GUI_component(ownerFilter))
, source_frame(new SSR::Source_frame_gui_component(ownerFilter))
{
  // Need to have a processor to get data (for example of the connection)
  Controller* processor = getProcessor();

  addAndMakeVisible(source_frame);
  addAndMakeVisible(head_frame);

  head_frame->setBounds                 (0,             0,        head_frame->getWidth(),                 head_frame->getHeight());
  source_frame->setBounds               (0,             100,      source_frame->getWidth(),               source_frame->getHeight());

  //TODO: Think about that...
  head_frame->set_connected(processor->is_connected_to_ssr());

  //All addAndMakeVisible objects have to be initialised before here!!
  setSize(900, 600);

  processor->read_ssr_incoming_message();

  //processor->ui_request_update();// UI update must be done each time a new editor is constructed
  startTimer(10);//starts timer with interval of 50mS
}

Main_GUI_component::~Main_GUI_component()
{
  removeAllChildren();
  source_frame      = nullptr;
  head_frame        = nullptr;
}

//==============================================================================
void Main_GUI_component::paint (Graphics& g)
{
  g.fillAll(SSR::colour::get_colour(SSR::colour::Colours::white));
  g.setColour(SSR::colour::get_colour(SSR::colour::Colours::black));
}

void Main_GUI_component::timerCallback()
{

  Controller* processor = getProcessor();

  if (processor->read_ssr_incoming_message() && processor->ui_needs_update()) {

      SSR::Source source = processor->get_source();

      head_frame->set_connected(processor->is_connected_to_ssr());

      source_frame->move_source(source.get_x_position().get_discrete_value(), source.get_y_position().get_discrete_value());
      source_frame->set_x_axis_slider_value(source.get_x_position().get_discrete_value());
      source_frame->set_y_axis_slider_value(source.get_y_position().get_discrete_value());

      source_frame->set_name_text_editor_text(juce::String(source.get_name()));
      source_frame->set_id_text_editor_text(juce::String(source.get_id()));
      source_frame->set_orientation_text_editor_text(String(source.get_orientation().get_discrete_value()));

      //Be carefull: When setting the new value, the parameter_source_gain has first to be converted from linear to dB!
      source_frame->set_gain_slider_value(SSR::Helper::linear_to_dB(source.get_gain().get_discrete_value()));
      source_frame->set_mute_button_toggle_state(source.get_mute().get_discrete_value());
      source_frame->set_fixed_button_toggle_state(source.get_fixed().get_discrete_value());

      bool model_point = source.get_model_point().get_discrete_value();

      if (model_point) {
          source_frame->set_model_selected_id(1);
      } else {
          source_frame->set_model_selected_id(2);
      }

      const std::string entry = source.get_jackport();
      source_frame->set_jackport_selected_entry(entry);

      source_frame->reload_source_dropdown();

      processor->ui_clear_update_flag();

  }

}
