#ifndef SOURCE_FRAME_GUI_COMPONENT_H
#define SOURCE_FRAME_GUI_COMPONENT_H

//C++ Libs
#include <memory>

//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

#include <src/GUI/source_frame/source_pad/source_pad_and_controls_gui_component.h>
#include <src/GUI/source_frame/source_parameters/source_parameters_gui_component.h>
#include <src/controller.h>

namespace SSR
{

  class Source_frame_gui_component : public juce::AudioProcessorEditor
  {

  public:
    Source_frame_gui_component(Controller* processor);
    ~Source_frame_gui_component();

    /**
     * This method returns the processor to do stuff with it.
     *
     * @return   the processor which is the controller of this software.
     **/
    Controller* getProcessor() const {
      return static_cast<Controller*>(getAudioProcessor());
    }

    void paint(juce::Graphics& graphics) override;

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
