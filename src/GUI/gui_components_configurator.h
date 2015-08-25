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
#include <JUCE/JuceHeader.h>

namespace SSR
{

  /**
   * Configures the transferred text_editor as follows:
   *
   * Multiline                  -> false
   * ReturnKeyStartsNewLine     -> false
   * ScrollbarsShown            -> true
   * PopupMenuEnabled           -> true
   *
   * ReadOnly                   -> Set to the transferred parameter read_only
   * CaretVisible               -> Set to the transferred parameter caret_visible
   * Text                       -> Set to the transferred parameter initial_text
   *
   * If the text_editor is read only, the inner color will be grey, white
   * otherwise.
   *
   * Please read the documentation for the TextEditor class for more detailed
   * information on what those setting do:
   *
   * http://learn.juce.com/doc/classTextEditor.php
   *
   * @see http://learn.juce.com/doc/classTextEditor.php
   *
   * @param     text_editor     The text editor which shall be configured.
   *
   * @param     read_only       Defines whether the text_editor shall be
   *                            read only (true) or not (false) by the user.
   *
   * @param     caret_visible   Defines whether the caret shall be visible
   *                            when entering the text field of the text_editor.
   *
   * @param     initial_text    The text that should initially be put into the
   *                            text_editor.
   */
  void configure_text_editor(juce::TextEditor& text_editor, const bool read_only, const bool caret_visible, const juce::String& initial_text);

  /**
   * Configures the transferred text_editor as follows:
   *
   * Multiline                  -> false
   * ReturnKeyStartsNewLine     -> false
   * ScrollbarsShown            -> true
   * PopupMenuEnabled           -> true
   *
   * ReadOnly                   -> Set to the transferred parameter read_only
   * CaretVisible               -> Set to the transferred parameter caret_visible
   * Text                       -> Set to the transferred parameter initial_text
   * InputRestrictions          -> Set to the transferred parameters max_length and input_restrictions
   *
   * If the text_editor is read only, the inner color will be grey, white
   * otherwise.
   *
   * Please read the documentation for the TextEditor class for more detailed
   * information on what those setting do:
   *
   * http://learn.juce.com/doc/classTextEditor.php
   *
   * @see http://learn.juce.com/doc/classTextEditor.php
   *
   * @param     text_editor     The text editor which shall be configured.
   *
   * @param     read_only       Defines whether the text_editor shall be
   *                            read only (true) or not (false) by the user.
   *
   * @param     caret_visible   Defines whether the caret shall be visible
   *                            when entering the text field of the text_editor.
   *
   * @param     max_length      Defines the max length of the text that the
   *                            user is able to put into the text_editor.
   *
   * @param     input_restrictions      Defines which characters are able to
   *                                    put into the text_editor.
   *
   * @param     initial_text    The text that should initially be put into the
   *                            text_editor.
   */
  void configure_text_editor(juce::TextEditor& text_editor, const bool read_only, const bool caret_visible, const int max_length, const juce::String& input_restrictions, const juce::String& initial_text);

  /**
   * Configures the transferred text_button as follows:
   *
   * ClickingTogglesState       -> true
   * ToggleState                -> false (dontSendNotification)
   * TriggeredOnMouseDown       -> true
   *
   * ButtonText                 -> Set to the transferred parameter text
   *
   *
   * Coloring:
   * Button color              -> SSR::colour::Colours::blue
   * Text color (On)           -> SSR::colour::Colours::white
   * Text color (Off)          -> SSR::colour::Colours::black
   *
   * @see ssr_colour.h
   *
   * Please read the documentation for the TextButton class for more detailed
   * information on what those setting do:
   *
   * http://learn.juce.com/doc/classTextButton.php
   *
   * @see http://learn.juce.com/doc/classTextButton.php
   *
   * @param     text_button     The text button which shall be configured.
   *
   * @param     text            The text that shall be shown on the text button.
   */
  void configure_text_button(juce::TextButton& text_button, const juce::String& text);

  /**
   * Configures the transferred label as follows:
   *
   * Editable                   -> false
   * JustificationType          -> Justification::centredRight
   * Font                       -> 15.0, Font::bold
   *
   * Coloring:
   * Text color                 -> SSR::colour::Colours::black
   * Background color           -> Set to the transferred parameter background_colour
   *
   * Please read the documentation for the TextEditor class for more detailed
   * information on what those setting do:
   *
   * http://learn.juce.com/doc/classLabel.php
   *
   * @see http://learn.juce.com/doc/classLabel.php
   *
   * @param     label                   The label that shall be configured.
   *
   * @param     background_colour       Defines the background color of the
   *                                    label.
   */
  void configure_label(juce::Label& label, juce::Colour& background_colour);

  /**
   * Configures the transferred combobox (dropdown) as follows:
   *
   * EditableText               -> false
   * JustificationType          -> Justification::centredLeft
   * TextWhenNothingSelected    -> "please select"
   *
   * TextWhenNoChoicesAvailable -> Set to the transferred parameter no_choice_available
   *
   * Please read the documentation for the ComboBox class for more detailed
   * information on what those setting do:
   *
   * http://learn.juce.com/doc/classComboBox.php
   *
   * @see http://learn.juce.com/doc/classComboBox.php
   *
   * @param     combobox                The combobox that shall be configured.
   *
   * @parm      no_choice_available     Text that will be shown if there is no
   *                                    no choice available.
   */
  void configure_dropdown(juce::ComboBox& combobox, const juce::String& no_choice_available);

  /**
   * Configures the transferred slider as follows:
   *
   * Range                      -> Set to the transferred parameters min, max and interval.
   * SliderStyle                -> Set to the transferred parameter style.
   *
   * Coloring:
   * thumbColour                -> SSR::colour::Colours::white
   * trackColour                -> SSR::colour::Colours::black
   *
   * Please read the documentation for the Slider class for more detailed
   * information on what those setting do:
   *
   * http://learn.juce.com/doc/classSlider.php
   *
   * @see http://learn.juce.com/doc/classSlider.php
   *
   * @param     slider          The slider that shall be configured.
   *
   * @param     min             The min range the slider shall be set to (begin of range).
   *
   * @param     max             The max range the slider shall be set to (end of range).
   *
   * @param     interval        The interval the slider shall be slide able.
   *
   * @param     style           The style of the slider.
   */
  void configure_slider(juce::Slider& slider, const double min, const double max, const double interval, juce::Slider::SliderStyle style);

  /**
   * Configures the transferred sliders textbox as follows:
   *
   * TextBoxStyle               -> Set to the transferred parameters position, read_only, width and height
   *
   * Please read the documentation for the Slider class for more detailed
   * information on what those setting do:
   *
   * http://learn.juce.com/doc/classSlider.php
   *
   * @see http://learn.juce.com/doc/classSlider.php
   *
   * @param     slider          The slider that shall be configured.
   *
   * @param     position        Defines the position of the sliders text box.
   *
   * @param     read_only       Defines if the text box is read only (true) or
   *                            not (false).
   *
   * @param     width           The width of the sliders text box.
   *
   * @param     height          The height of the sliders text box.
   */
  void configure_slider_textbox(juce::Slider& slider, Slider::TextEntryBoxPosition position, const bool read_only, const int width, const int height);

}

#endif
