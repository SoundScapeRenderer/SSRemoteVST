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

//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

//C++ Libs
#include <memory>

//Own Libs
#include <src/GUI/source_frame/source_pad/source_pad_gui_component.h>
#include <src/GUI/source_frame/source_pad/zoom_gui_component.h>
#include <src/controller.h>

namespace SSR
{

  class Source_pad_and_controls_gui_component
  : public juce::AudioProcessorEditor
  , public juce::Slider::Listener
  , public juce::ChangeListener
  {

  public:

    Source_pad_and_controls_gui_component(Controller* processor);

    ~Source_pad_and_controls_gui_component();

    void move_source(const float absolute_x_position, const float absolute_y_position);

    /**
     * This method returns the processor to do stuff with it.
     *
     * @return   the processor which is the controller of this software.
     **/
    Controller* getProcessor() const {
      return static_cast<Controller*>(getAudioProcessor());
    }

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

    void changeListenerCallback(ChangeBroadcaster *source);

    void set_x_axis_slider_value(const double value);

    void set_y_axis_slider_value(const double value);

  private:
    std::unique_ptr<SSR::Source_pad_gui_component> pad;
    std::unique_ptr<juce::Slider> x_axis_slider;
    std::unique_ptr<juce::Slider> y_axis_slider;
    std::unique_ptr<SSR::Zoom_GUI_component> zoom;

  };

}

#endif
