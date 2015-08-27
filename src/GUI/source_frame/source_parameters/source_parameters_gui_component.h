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

  /**
   * This class represents the 'Source Parameters GUI Component' including
   * GUI components relating the parameters to control the sources including
   * the following parameters (r = readable, w = writeable):
   *
   * - Fixed (r/w)
   * - Mute (r/w)
   * - Name (r/w)
   * - Orientation (r)
   * - Gain (r/w)
   * - Source Dropdown (for choosing which source to manipulate) (r/w)
   * - Jackport Dropdown (for chossing the jackport the source shall connect to) (r/w)
   * - Model (r/w)
   *
   */
  class Source_parameters_gui_component
      : public juce::AudioProcessorEditor
      , public juce::Button::Listener
      , public juce::ComboBox::Listener
      , public juce::TextEditor::Listener
      , public juce::Slider::Listener
  {

  public:

    /**
     * Constructor initialising and configuring all GUI components.
     *
     * Sets the size of this GUI component to 450x400 pixels.
     *
     * @param   controller      Controller needed to r/w data.
     */
    Source_parameters_gui_component(Controller* controller);

    /**
     * Destructor.
     */
    ~Source_parameters_gui_component();

    /**
     * JUCE Doc.: Called when the button is clicked.
     *
     * @see http://www.juce.com/api/classButton_1_1Listener.html#a81499cef24b7189cd0d1581fd9dc9e14
     *
     * The controller will be noticed if the mute_button or fixed_button was
     * clicked.
     *
     * @param           buttonThatWasClicked            The button that was clicked.
     */
    void buttonClicked(juce::Button* buttonThatWasClicked) override;

    /**
     * JUCE Doc.:       Called when the slider's value is changed.
     *                  This may be caused by dragging it, or by typing in its text
     *                  entry box, or by a call to Slider::setValue().
     *
     * @see http://www.juce.com/api/classSlider_1_1Listener.html#a127bfe68835dc3e584cf3c2a427a27e5
     * @see http://www.juce.com/api/classSlider.html#a430a5c4e56b39dd622f5800f787e0822
     * @see http://www.juce.com/api/classSlider.html#ace4fffe8ad4e2b2c4cd2cda06dedc848
     *
     * The controller will be noticed if the gain_slider was moved.
     *
     * @param           sliderThatWasMoved      The slider that was moved.
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
     * The controller will be noticed if the jackport_dropdown, the model_dropdown
     * or the sources_dropwdown has been changed.
     *
     * @param   comboBoxThatHasChanged          The combobox that has changed.
     */
    void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;

    /**
     * Inherited from JUCE TextEditorListener Class.
     *
     * This method is called when a TextEditor UI element was changed and the
     * return key was pressed.
     *
     * The controller will be noticed if the return key was pressd in th
     * name_text_editor  (which means that there is a new name for the source).
     * Additionally, the name_text_editor_is_changing member will be set to
     * false.
     *
     * @param    textEditorThatWasChanged    The text Editor that was changed.
     **/
    void textEditorReturnKeyPressed(TextEditor &textEditorThatWasChanged) override;

    /**
     * Inherited from JUCE TextEditorListener Class.
     *
     * This method is called when a TextEditor UI element is changing.
     *
     * The member name_text_editor_is_changing will be set to true if the
     * text editor which text is changing is the name_text_editor.
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
     * The member name_text_editor_is_changing will be set to false if the
     * text editor which lost the focus is the name_text_editor.
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

    /**
     * Sets the gain sliders value to the transferred value.
     *
     * @param   value           The value to which the gain slider shall be set.
     */
    void set_gain_slider_value(const float value);

    /**
     * Sets the selected ID of the model_dropdown to the transferred id.
     *
     * @param   id              The ID to which the model_dropdown shall be set.
     */
    void set_model_selected_id(const int id);

    /**
     * Sets the selected entry of the jackport_dropdown to the entry equal
     * to the transferred entry.
     *
     * If the transferred entry is unequal to every entry existing in the
     * jackport_dropdown, an error will be logged.
     *
     * @param   entry           The entry which shall be selected by in the
     *                          jackport_dropdown.
     */
    void set_jackport_selected_entry(const std::string& entry);

    /**
     * Sets the mute button toggle state to the transferred state.
     *
     * @param   state           The state to which the mute button shall be
     *                          toggled.
     */
    void set_mute_button_toggle_state(const bool state);

    /**
     * Sets the fixed button toggle state to the transferred state.
     *
     * @param   state           The state to which the fixed button shall be
     *                          toggled.
     */
    void set_fixed_button_toggle_state(const bool state);

    void set_name_text_editor_text(const juce::String& text);

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

  };

}

#endif
