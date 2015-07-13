#ifndef SOURCE_PARAMETERS_GUI_COMPONENT
#define SOURCE_PARAMETERS_GUI_COMPONENT

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
#include <memory>
#include <string>
#include <map>

#include <src/controller.h>

namespace SSR
{

  class Source_parameters_gui_component : public juce::AudioProcessorEditor
  , public juce::Button::Listener
  , public juce::ComboBox::Listener
  , public juce::TextEditor::Listener
  , public juce::Slider::Listener
  {

  public:
    Source_parameters_gui_component(Controller* processor);

    ~Source_parameters_gui_component();

    /**
     * JUCE Doc.: Called when the button is clicked.
     *
     * @see http://www.juce.com/api/classButton_1_1Listener.html#a81499cef24b7189cd0d1581fd9dc9e14
     *
     * @param           buttonThatWasClicked            The button that was clicked.
     *
     * @author          Florian Willich
     */
    void buttonClicked(juce::Button* buttonThatWasClicked) override;

    /**
     * JUCE Doc.:       Called when the slider's value is changed.
     *                  This may be caused by dragging it, or by typing in its text
     *                  entry box, or by a call to Slider::setValue().
     *
     * You can find out the new value using Slider::getValue().
     *
     * @see http://www.juce.com/api/classSlider_1_1Listener.html#a127bfe68835dc3e584cf3c2a427a27e5
     * @see http://www.juce.com/api/classSlider.html#a430a5c4e56b39dd622f5800f787e0822
     * @see http://www.juce.com/api/classSlider.html#ace4fffe8ad4e2b2c4cd2cda06dedc848
     *
     * @param           sliderThatWasMoved      The slider that was moved.
     *
     * @author Florian Willich
     */
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;

    /**
     * JUCE Doc.:       Called when a ComboBox has its selected item changed.
     *                  Implemented in FileBrowserComponent.
     *
     * @see http://www.juce.com/api/classComboBox_1_1Listener.html#a9ed3676ad921acde0414966fc41f1000
     * @see http://www.juce.com/api/classComboBox.html
     * @see http://www.juce.com/api/classFileBrowserComponent.html#a8e55a512b35b04dce0a9c16ef5028487
     *
     * @param   comboBoxThatHasChanged          The combobox that has changed.
     *
     * @author  Florian Willich
     */
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    /**
     * Inherited from JUCE TextEditorListener Class.
     *
     * This method is called when a TextEditor UI element was changed and the
     * return key was pressed.
     *
     * @param    textEditorThatWasChanged    The text Editor that was changed.
     **/
    void textEditorReturnKeyPressed(TextEditor &textEditorThatWasChanged) override;

    /**
     * Inherited from JUCE TextEditorListener Class.
     *
     * This method is called when a TextEditor UI element is changing.
     *
     * @param    text_editor_thats_changing      The text Editor that is
     *                                           currently changing.
     **/
    void textEditorTextChanged(TextEditor& text_editor_thats_changing) override;

    /**
     * Inherited from JUCE TextEditorListener Class.
     *
     * This method is called when the focus of a TextEditor element is lost. The
     * JUCE documentation says the folloging:
     * "Called when the text editor loses focus."
     *
     * @param    text_editor_focus_lost      The text editor which focus is lost.
     **/
    void textEditorFocusLost(TextEditor& text_editor_focus_lost) override;

    /**
     * This method returns the processor to do stuff with it.
     *
     * @return   the processor which is the controller of this software.
     **/
    Controller* getProcessor() const {
      return static_cast<Controller*>(getAudioProcessor());
    }

    void set_gain_slider_value(const float value);

    void set_model_selected_id(const int id);

    void set_jackport_selected_entry(const std::string& entry);

    void set_mute_button_toggle_state(const bool state);

    void set_fixed_button_toggle_state(const bool state);

    void set_id_text_editor_text(const juce::String& text);

    void set_name_text_editor_text(const juce::String& text);

    void set_orientation_text_editor_text(const juce::String& text);

    void fill_jackport_dropdown();

    void reload_source_dropdown();
  private:
    void make_all_visible();
    void configure_all_components();
    void configure_text_editors();
    void configure_text_buttons();
    void configure_labels();
    void configure_dropdowns();
    void configure_sliders();
    void set_text_editor_text(juce::TextEditor& texteditor, const juce::String& text, bool is_changing);
    void set_bounds();

  private:
    std::unique_ptr<juce::Label> source_label;
    std::unique_ptr<juce::Label> name_label;
    std::unique_ptr<juce::Label> orientation_label;
    std::unique_ptr<juce::Label> jackport_label;
    std::unique_ptr<juce::Label> model_label;
    std::unique_ptr<juce::Label> gain_label;

    std::unique_ptr<juce::TextButton> fixed_button;
    std::unique_ptr<juce::TextButton> mute_button;
    std::unique_ptr<juce::TextEditor> name_text_editor;
    std::unique_ptr<juce::TextEditor> orientation_text_editor;

    std::unique_ptr<juce::Slider> gain_slider;

    std::unique_ptr<juce::ComboBox> sources_dropwdown;
    std::unique_ptr<juce::ComboBox> jackport_dropdown;
    std::unique_ptr<juce::ComboBox> model_dropdown;



    /**
     * This vector is needed to store all ids that have been put in
     **/
    std::map<int, std::string> jackport_dropdown_menu_entries;

    /**
     * Represents if the Source Name Text Editor UI element is currently
     * changing.
     **/
    bool name_text_editor_is_changing;

    /**
     * Represents if the Source Orientation Text Editor UI element is currently
     * changing.
     **/
    bool source_orientation_text_editor_is_changing;

    /**
     * Represents if the Source ID Text Editor UI element is currently
     * changing.
     **/
    bool id_text_editor_is_changing;

    /**
     * Represents if the Source Properties File Text Editor UI element is
     * currently changing.
     **/
    bool properties_file_text_editor_is_changing;

  };

}

#endif
