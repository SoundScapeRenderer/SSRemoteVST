#ifndef SOURCE_PAD_AND_CONTROLS_GUI_COMPONENT_H
#define SOURCE_PAD_AND_CONTROLS_GUI_COMPONENT_H

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

//C++ Libs
#include <memory>

//Own Libs
#include <src/GUI/source_frame/source_pad/source_pad_gui_component.h>
#include <src/GUI/source_frame/source_pad/zoom_gui_component.h>
#include <src/controller.h>

namespace SSR
{

  /**
   * This class represents the 'Source Pad and Controls GUI Component'
   * including a pad where the the source moves on a grid, two sliders
   * with which the user is able to control the sources position and a zoom
   * component with which the user is able to zoom in and out.
   */
  class Source_pad_and_controls_gui_component
      : public juce::AudioProcessorEditor
      , public juce::Slider::Listener
      , public juce::ChangeListener
  {

  public:

    /**
     * Constructor initialising the pad with 350x350 pixels, and configuring
     * all related GUI components.
     *
     * Sets the size of this GUI component to 500x500 pixels.
     *
     * @param   controller      Controller to read and write data.
     */
    Source_pad_and_controls_gui_component(Controller* controller);

    /**
     * Destructor.
     */
    ~Source_pad_and_controls_gui_component();

    /**
     * Moves the source to the transferred X (discrete_x_position) and
     * Y (discrete_y_position) position.
     *
     * @param   discrete_x_position     The discrete X position to which the
     *                                  source shall be moved.
     *
     * @param   discrete_y_position     The discrete Y position to which the
     *                                  source shall be moved.
     */
    void move_source(const float discrete_x_position, const float discrete_y_position);

    /**
     * This method returns the processor to do stuff with it.
     *
     * @return   the processor which is the controller of this software.
     **/
    Controller* getProcessor() const {
      return static_cast<Controller*>(getAudioProcessor());
    }

    /**
     * If the sliderThatWasMoved is the x_axis_slider, the X position of the
     * source will be changed to the value of the sliders position.
     *
     * If the sliderThatWasMoved is the y_axis_slider, the Y position of the
     * source will be changed to the value of the sliders position.
     *
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
     */
    void sliderValueChanged(juce::Slider* sliderThatWasMoved) override;

    /**
     * If the source is the zoom component, the x_axis_slider, the y_axis_slider
     * and the pad ranges will be updated.
     *
     * For more information on this method please read the JUCE documentation:
     *
     * http://learn.juce.com/doc/classChangeListener.php#a027420041071315201df11e19a36ea18
     *
     * @see http://learn.juce.com/doc/classChangeListener.php#a027420041071315201df11e19a36ea18
     *
     * @param           source          The ChangeBroadcaster that triggered the callback.
     */
    void changeListenerCallback(ChangeBroadcaster *source);

    /**
     * Sets the current value of the x_axis_slider slider to the transferred
     * value.
     *
     * @param           value           The value the x_axis_slider shall be
     *                                  set to.
     */
    void set_x_axis_slider_value(const double value);

    /**
     * Sets the current value of the y_axis_slider slider to the transferred
     * value.
     *
     * @param           value           The value the y_axis_slider shall be
     *                                  set to.
     */
    void set_y_axis_slider_value(const double value);

  private:

    /**
     * The source pad.
     */
    std::unique_ptr<SSR::Source_pad_gui_component> pad;

    /**
     * The x axis slider.
     */
    std::unique_ptr<juce::Slider> x_axis_slider;

    /**
     * The Y axis slider.
     */
    std::unique_ptr<juce::Slider> y_axis_slider;

    /**
     * The zoom component.
     */
    std::unique_ptr<SSR::Zoom_GUI_component> zoom;

  };

}

#endif
