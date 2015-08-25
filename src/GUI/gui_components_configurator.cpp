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

#include <src/GUI/gui_components_configurator.h>
#include <src/config/ssr_colour.h>

void SSR::configure_text_editor(juce::TextEditor& text_editor, const bool read_only, const bool caret_visible, const juce::String& initial_text)
{
  text_editor.setMultiLine(false);
  text_editor.setReturnKeyStartsNewLine(false);
  text_editor.setReadOnly(read_only);
  text_editor.setScrollbarsShown(true);
  text_editor.setCaretVisible(caret_visible);
  text_editor.setPopupMenuEnabled(true);
  text_editor.setText(initial_text);

  juce::Colour inner_colour = read_only ? SSR::colour::get_colour(SSR::colour::Colours::foreground_grey) : SSR::colour::get_colour(SSR::colour::Colours::white);
  text_editor.setColour(TextEditor::backgroundColourId, inner_colour);
}

void SSR::configure_text_editor(juce::TextEditor& text_editor, const bool read_only, const bool caret_visible, const int max_length, const juce::String& input_restrictions, const juce::String& initial_text)
{
  configure_text_editor(text_editor, read_only, caret_visible, initial_text);

  text_editor.setInputRestrictions(max_length, input_restrictions);
}

void SSR::configure_text_button(juce::TextButton& text_button, const juce::String& text)
{
  text_button.setButtonText(TRANS(text));
  text_button.setColour(TextButton::buttonColourId, SSR::colour::get_colour(SSR::colour::Colours::blue));
  text_button.setColour(TextButton::textColourOnId, SSR::colour::get_colour(SSR::colour::Colours::white));
  text_button.setColour(TextButton::textColourOffId, SSR::colour::get_colour(SSR::colour::Colours::black));
  text_button.setClickingTogglesState(true);
  text_button.setToggleState(false, juce::dontSendNotification);
  text_button.setTriggeredOnMouseDown(true);
}

void SSR::configure_label(juce::Label& label, juce::Colour& background_colour)
{
  label.setFont(juce::Font(15.0f, Font::bold));
  label.setJustificationType(Justification::centredRight);
  label.setEditable(false, false, false);
  label.setColour(Label::textColourId, SSR::colour::get_colour(SSR::colour::Colours::black));
  label.setColour(Label::backgroundColourId, background_colour);
}


void SSR::configure_dropdown(juce::ComboBox& combobox, const juce::String& no_choice_available)
{
  combobox.setEditableText(false);
  combobox.setJustificationType(Justification::centredLeft);
  combobox.setTextWhenNothingSelected (TRANS("please select"));
  combobox.setTextWhenNoChoicesAvailable (TRANS(no_choice_available));
}

void SSR::configure_slider(juce::Slider& slider, const double min, const double max, const double interval, juce::Slider::SliderStyle style)
{
  slider.setRange(min, max, interval);
  slider.setSliderStyle(style);
  slider.setColour(Slider::thumbColourId, SSR::colour::get_colour(SSR::colour::Colours::white));
  slider.setColour(Slider::trackColourId, SSR::colour::get_colour(SSR::colour::Colours::black));
}

void SSR::configure_slider_textbox(juce::Slider& slider, Slider::TextEntryBoxPosition position, const bool read_only, const int width, const int height)
{
  slider.setTextBoxStyle(position, read_only, width, height);
}
