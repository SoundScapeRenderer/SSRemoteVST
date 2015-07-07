#ifndef GUI_COMPONENTS_CONFIGURATOR_H
#define GUI_COMPONENTS_CONFIGURATOR_H

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
#include <src/JuceHeader.h>

namespace SSR
{
  void configure_text_editor(juce::TextEditor& text_editor, const bool read_only, const bool caret_visible, const int max_length, const juce::String& initial_text);
  void configure_text_editor(juce::TextEditor& text_editor, const bool read_only, const bool caret_visible, const int max_length, const juce::String& input_restrictions, const juce::String& initial_text);
  void configure_text_button(juce::TextButton& text_button, const juce::String& text);
  void configure_label(juce::Label& label, juce::Colour& background_colour);
  void configure_dropdown(juce::ComboBox& combobox, const juce::String& no_choice_available);
  void configure_slider(juce::Slider& slider, const double min, const double max, const double interval, juce::Slider::SliderStyle style);
  void configure_slider_textbox(juce::Slider& slider, Slider::TextEntryBoxPosition position, const bool read_only, const int width, const int height);
}

#endif
