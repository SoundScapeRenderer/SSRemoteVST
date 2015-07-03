#ifndef SOURCE_GUI_COMPONENT_H
#define SOURCE_GUI_COMPONENT_H

//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

//C++ Libs
#include <memory>

namespace SSR
{

  class Source_gui_component : public juce::Component
  {

  public:
    Source_gui_component();
    Source_gui_component(const unsigned int width_and_height);
    ~Source_gui_component();
    void paint(juce::Graphics& graphics) override;
    float get_radius() const;

  private:
    float radius;
    std::unique_ptr< juce::Point<float> > location;
    void draw_background(juce::Graphics& graphics);

  };


}

#endif
