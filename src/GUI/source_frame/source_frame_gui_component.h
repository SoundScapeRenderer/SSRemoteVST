#ifndef SOURCE_FRAME_GUI_COMPONENT_H
#define SOURCE_FRAME_GUI_COMPONENT_H

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

//C++ Libs
#include <memory>

//JUCE Lib
#include <JUCE/JuceHeader.h>

#include <src/GUI/source_frame/source_pad/source_pad_and_controls_gui_component.h>
#include <src/GUI/source_frame/source_parameters/source_parameters_gui_component.h>
#include <src/controller.h>

namespace SSR
{

  /**
   * This class represents the 'Source Frame GUI Component' including all
   * GUI components relating the Source.
   *
   *
   */
  class Source_frame_gui_component
      : public juce::AudioProcessorEditor
  {

  public:

    /**
     * Constructor configurating the related GUI components.
     *
     * Sets the size of this GUI frame to 900x500 pixels.
     *
     * Loads the ssr_logo_large.png from the following path:
     * SSREMOTE_VST/src/images/ssr_logo_large.png
     *
     * Where SSREMOTE_VST is the environment variable.
     *
     * @param   controller      Controller needed to r/w data.
     */
    Source_frame_gui_component(Controller* controller);

    /**
     * Destructor.
     */
    ~Source_frame_gui_component();

    /**
     * This method returns the processor to do stuff with it.
     *
     * @return   the processor which is the controller of this software.
     **/
    Controller* getProcessor() const {
      return static_cast<Controller*>(getAudioProcessor());
    }

    /**
     * Like the JUCE documentation say:
     * "The paint() method gets called when a region of a component needs
     * redrawing, either because the component's repaint() method has been
     * called, or because something has happened on the screen that means a
     * section of a window needs to be redrawn."
     *
     * @see             http://www.juce.com/api/classComponent.html#a7cf1862f4af5909ea72827898114a182
     *
     * Fills the background with white and creates a rounded rectangle with
     * the background grey color.
     *
     * @see ssr_colour.h
     *
     * @param           graphics       the graphics context that must be used
     *                                 to do the drawing operations.
     */
    void paint(juce::Graphics& graphics) override;

    /**
     * Moves the source to the transferred X (discrete_x_position) and
     * Y (discrete_y_position) position.
     *
     * @see source_pad_and_controls_gui_component.h
     *
     * @param   discrete_x_position     The discrete X position to which the
     *                                  source shall be moved.
     *
     * @param   discrete_y_position     The discrete Y position to which the
     *                                  source shall be moved.
     */
    void move_source(const float discrete_x_position, const float discrete_y_position);

    /**
     * Sets the current value of the x_axis_slider slider to the transferred
     * value.
     *
     * @see source_pad_and_controls_gui_component.h
     *
     * @param           value           The value the x_axis_slider shall be
     *                                  set to.
     */
    void set_x_axis_slider_value(const double value);

    /**
     * Sets the current value of the y_axis_slider slider to the transferred
     * value.
     *
     * @see source_pad_and_controls_gui_component.h
     *
     * @param           value           The value the y_axis_slider shall be
     *                                  set to.
     */
    void set_y_axis_slider_value(const double value);

    /**
     * Sets the gain sliders value to the transferred value.
     *
     * @see source_parameters_gui_component.h
     *
     * @param   value           The value to which the gain slider shall be set.
     */
    void set_gain_slider_value(const float value);

    /**
     * Sets the selected ID of the model_dropdown to the transferred id.
     *
     * @see source_parameters_gui_component.h
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
     * @see source_parameters_gui_component.h
     *
     * @param   entry           The entry which shall be selected by in the
     *                          jackport_dropdown.
     */
    void set_jackport_selected_entry(const std::string& entry);

    /**
     * Sets the mute button toggle state to the transferred state.
     *
     * @see source_parameters_gui_component.h
     *
     * @param   state           The state to which the mute button shall be
     *                          toggled.
     */
    void set_mute_button_toggle_state(const bool state);

    /**
     * Sets the fixed button toggle state to the transferred state.
     *
     * @see source_parameters_gui_component.h
     *
     * @param   state           The state to which the fixed button shall be
     *                          toggled.
     */
    void set_fixed_button_toggle_state(const bool state);

    /**
     * Sets the text of the name_text_editor to the transferred text.
     *
     * @see source_parameters_gui_component.h
     *
     * @param   text            The text the name_text_editor shall be set to.
     */
    void set_name_text_editor_text(const juce::String& text);

    /**
     * Clears all the data of source_dropdown and fills it with the current
     * available sources and sets the selected source to the current selected
     * source of the controller.
     *
     * @see source_parameters_gui_component.h
     */
    void reload_source_dropdown();

  private:

    /**
     * The source pad and controls GUI component.
     */
    std::unique_ptr<SSR::Source_pad_and_controls_gui_component> source_pad_and_controls;

    /**
     * All source parameters.
     */
    std::unique_ptr<SSR::Source_parameters_gui_component> source_parameters;

    /**
     * The image GUI component for the SSR logo.
     */
    std::unique_ptr<juce::ImageComponent> ssr_logo_gui_component;

    /**
     * The SSR logo image.
     */
    std::unique_ptr<juce::Image> ssr_logo_image;

  };

}

#endif
