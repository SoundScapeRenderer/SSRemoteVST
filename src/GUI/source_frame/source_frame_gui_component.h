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
     *
     */
    void move_source(const float x, const float y);

    void set_x_axis_slider_value(const double value);

    void set_y_axis_slider_value(const double value);

    void set_gain_slider_value(const float value);

    void set_model_selected_id(const int id);

    void set_jackport_selected_entry(const std::string& entry);

    void set_mute_button_toggle_state(const bool state);

    void set_fixed_button_toggle_state(const bool state);

    void set_id_text_editor_text(const juce::String& text);

    void set_name_text_editor_text(const juce::String& text);

    void set_orientation_text_editor_text(const juce::String& text);

    void reload_source_dropdown();

  private:
    std::unique_ptr<SSR::Source_pad_and_controls_gui_component> source_pad_and_controls;
    std::unique_ptr<SSR::Source_parameters_gui_component> source_parameters;
    std::unique_ptr<juce::ImageComponent> ssr_image_component;
    std::unique_ptr<juce::Image> ssr_image;
    std::unique_ptr<juce::File> ssr_image_file;

  };

}

#endif
