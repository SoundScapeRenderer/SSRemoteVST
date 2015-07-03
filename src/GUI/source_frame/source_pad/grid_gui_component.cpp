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

#include <src/GUI/source_frame/source_pad/grid_gui_component.h>

//C++ Libs
#include <memory>

//Own Libs
#include <src/config/ssr_colour.h>

SSR::Grid_gui_component::Grid_gui_component(unsigned int width, unsigned int height)
: Component("GUI_component_grid")
, rect(nullptr)
, width(width)
, height(height)
{
  rect = std::unique_ptr< const juce::Rectangle<int> >(new const juce::Rectangle<int>(0, 0, width, height));

  setSize(width, height);
}

SSR::Grid_gui_component::~Grid_gui_component()
{
  removeAllChildren();
  rect = nullptr;
}

void SSR::Grid_gui_component::paint(Graphics& graphics)
{
  draw_background(graphics);
  draw_border(graphics);
  draw_axes(graphics);
}

const juce::Rectangle<int> SSR::Grid_gui_component::get_rect() const
{
  return *rect;
}

void SSR::Grid_gui_component::draw_background(Graphics& graphics)
{
  graphics.setColour(SSR::colour::get_colour(SSR::colour::Colours::foreground_grey));
  graphics.fillRoundedRectangle(rect->getPosition().x, rect->getPosition().y, rect->getWidth(), rect->getHeight(), 0.0f);
}

void SSR::Grid_gui_component::draw_border(Graphics& graphics)
{
  graphics.setColour(SSR::colour::get_colour(SSR::colour::Colours::black));
  graphics.drawRoundedRectangle(rect->getPosition().x, rect->getPosition().y, rect->getWidth(), rect->getHeight(), 0.0f, 2.0f);
}

void SSR::Grid_gui_component::draw_axes(Graphics& graphics)
{
  graphics.setColour(juce::Colours::grey);

  //Draw Vertical Line
  float start_x = width / 2.0f;
  float start_y = 0.0f;
  float end_x = start_x;
  float end_y = height;
  graphics.drawLine(start_x, start_y, end_x, end_y, 2.0f);

  //Draw Horizontal Line
  start_x = 0.0f;
  start_y = height / 2.0f;
  end_x = width;
  end_y = start_y;
  graphics.drawLine(start_x, start_y, end_x, end_y, 2.0f);
}
