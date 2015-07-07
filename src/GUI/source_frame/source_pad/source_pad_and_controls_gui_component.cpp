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
#include <src/GUI/source_frame/source_pad/source_pad_and_controls_gui_component.h>

//JUCE Lib
#include <src/JuceHeader.h>

//Own Libs
#include <src/GUI/gui_components_configurator.h>
#include <src/GUI/source_frame/source_pad/zoom_gui_component.h>

//C++ Libs
#include <memory>

SSR::Source_pad_and_controls_gui_component::Source_pad_and_controls_gui_component(Controller* processor)
: AudioProcessorEditor(processor)
, pad(new Source_pad_gui_component(350, 350))
, x_axis_slider(new juce::Slider("x_axis_slider"))
, y_axis_slider(new juce::Slider("y_axis_slider"))
, zoom(new SSR::Zoom_GUI_component())
{
  addAndMakeVisible(*pad);
  pad->setBounds(0, 0, pad->getWidth(), pad->getHeight());

  addAndMakeVisible(*x_axis_slider);
  x_axis_slider->setBounds(0, 370, 350, 50);

  addAndMakeVisible(*y_axis_slider);
  y_axis_slider->setBounds(370, 0, 100, 350);

  addAndMakeVisible(*zoom);
  zoom->setBounds(pad->getWidth() - zoom->getWidth() - 5, pad->getHeight() - zoom->getHeight() - 5, zoom->getWidth(), zoom->getHeight());
  zoom->addChangeListener(this);

  double min = -1.0f * zoom->get_current_range() / 2.0f;
  double max = zoom->get_current_range() / 2.0f;
  SSR::configure_slider(*x_axis_slider, min, max, 0.01, juce::Slider::SliderStyle::LinearHorizontal);
  SSR::configure_slider_textbox(*x_axis_slider, juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 71, 25);
  x_axis_slider->addListener(this);

  SSR::configure_slider(*y_axis_slider, min, max, 0.01, juce::Slider::SliderStyle::LinearVertical);
  SSR::configure_slider_textbox(*y_axis_slider, juce::Slider::TextEntryBoxPosition::TextBoxRight, false, 71, 25);
  y_axis_slider->addListener(this);

  setSize(500, 500);
}

SSR::Source_pad_and_controls_gui_component::~Source_pad_and_controls_gui_component()
{
  removeAllChildren();
  pad                           = nullptr;
  x_axis_slider                 = nullptr;
  y_axis_slider                 = nullptr;
  zoom                          = nullptr;
}

void SSR::Source_pad_and_controls_gui_component::move_source(const float absolute_x_position, const float absolute_y_position)
{
  pad->move_source(absolute_x_position, absolute_y_position, zoom->get_current_range());
}

void SSR::Source_pad_and_controls_gui_component::sliderValueChanged(juce::Slider* sliderThatWasMoved)
{
  Controller* processor = getProcessor();

  if (sliderThatWasMoved == x_axis_slider.get()) {
      processor->set_parameter_source_x_position(x_axis_slider->getValue());
  } else if (sliderThatWasMoved == y_axis_slider.get()) {
      processor->set_parameter_source_y_position(y_axis_slider->getValue());
  }

}

void SSR::Source_pad_and_controls_gui_component::changeListenerCallback(ChangeBroadcaster *source)
{

  if (source == zoom.get()) {
      double current_range = zoom->get_current_range();
      double min = -1.0f * current_range / 2.0f;
      double max = current_range / 2.0f;
      x_axis_slider->setRange(min, max, 0.01);
      y_axis_slider->setRange(min, max, 0.01);
      pad->update_range(current_range);
      pad->set_reference_range(current_range);
  }

}

void SSR::Source_pad_and_controls_gui_component::set_x_axis_slider_value(const double value)
{
  x_axis_slider->setValue(value, juce::NotificationType::dontSendNotification);
}

void SSR::Source_pad_and_controls_gui_component::set_y_axis_slider_value(const double value)
{
  y_axis_slider->setValue(value, juce::NotificationType::dontSendNotification);
}
