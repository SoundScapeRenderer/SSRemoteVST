#include <src/GUI/source_frame/source_pad/source_gui_component.h>

//Own Libs
#include <src/config/ssr_colour.h>

SSR::Source_gui_component::Source_gui_component()
: location(new juce::Point<float>(0.0f, 0.0f))
, radius(0.0f)
{
  radius = 40.0f / 2.0f;
  setSize(40.0f, 40.0f);
}

SSR::Source_gui_component::Source_gui_component(const unsigned int width_and_height)
: location(new juce::Point<float>(0.0f, 0.0f))
, radius(width_and_height / 2.0f)
{
  setSize(width_and_height, width_and_height);
}

SSR::Source_gui_component::~Source_gui_component()
{
  location = nullptr;
}

float SSR::Source_gui_component::get_radius() const
{
  return radius;
}

void SSR::Source_gui_component::paint(Graphics& graphics)
{
  draw_background(graphics);
}

void SSR::Source_gui_component::draw_background(juce::Graphics& graphics)
{
  graphics.setColour(SSR::colour::get_colour(SSR::colour::Colours::white));
  graphics.fillEllipse(0.0f, 0.0f, getWidth(), getHeight());

  graphics.setColour(SSR::colour::get_colour(SSR::colour::Colours::purple));
  graphics.drawEllipse(2.0f, 2.0f, getWidth() - 4.0f, getHeight() - 4.0f, 3.0f);
}
