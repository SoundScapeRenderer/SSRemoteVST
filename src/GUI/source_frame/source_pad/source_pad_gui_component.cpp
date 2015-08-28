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

#include <src/GUI/source_frame/source_pad/source_pad_gui_component.h>

SSR::Source_pad_gui_component::Source_pad_gui_component(int width, int heigth)
: Component("GUI_component_source_pad")
, grid(nullptr)
, source(new SSR::Source_gui_component())
, scale_reference(new SSR::Scale_reference_GUI_component(width, 5))
, current_discrete_x_position(0.0f)
, current_discrete_y_position(0.0f)
{
  grid = std::unique_ptr<SSR::Grid_gui_component>(new SSR::Grid_gui_component(width, heigth));

  addAndMakeVisible(*grid);
  grid->setBounds(0, 0, grid->getWidth(), grid->getHeight());

  addAndMakeVisible(*source);
  source->setBounds(width / 2.0f - source->get_radius(), heigth / 2.0f - source->get_radius(), source->getWidth(), source->getHeight());

  addAndMakeVisible(*scale_reference);
  scale_reference->setBounds(5, width - 5 - scale_reference->getHeight(), scale_reference->getWidth(), scale_reference->getHeight());

  setSize(width, heigth);
}

SSR::Source_pad_gui_component::~Source_pad_gui_component()
{
  removeAllChildren();
}

void SSR::Source_pad_gui_component::move_source(const float discrete_x_position, const float discrete_y_position, const double range)
{
  current_discrete_x_position = discrete_x_position;
  current_discrete_y_position = discrete_y_position;
  move_source_continuously(compute_continuous_position(true, discrete_x_position, range), compute_continuous_position(false, discrete_y_position, range));
}

void SSR::Source_pad_gui_component::update_range(const double range)
{
  move_source_continuously(compute_continuous_position(true, current_discrete_x_position, range), compute_continuous_position(false, current_discrete_y_position, range));
}

void SSR::Source_pad_gui_component::set_reference_range(const double new_reference_range)
{
  scale_reference->set_reference_range(new_reference_range);
}

/**
 * PRIVATE
 */

void SSR::Source_pad_gui_component::move_source_continuously(const float continuous_x_position, const float continuous_y_position)
{
  float source_discrete_x_position = continuous_x_position * getWidth() - source->get_radius();
  source_discrete_x_position = source_discrete_x_position < 0.0f ? 0.0f : source_discrete_x_position;
  source_discrete_x_position = source_discrete_x_position > getWidth() - source->getWidth() ? getWidth() - source->getWidth() : source_discrete_x_position;

  float source_discrete_y_position = continuous_y_position * getWidth() - source->get_radius();
  source_discrete_y_position = source_discrete_y_position < 0.0f ? 0.0f : source_discrete_y_position;
  source_discrete_y_position = source_discrete_y_position > getHeight() - source->getHeight() ? getHeight() - source->getHeight() : source_discrete_y_position;

  source->setBounds(source_discrete_x_position, source_discrete_y_position, source->getWidth(), source->getHeight());
  source->repaint();
}

float SSR::Source_pad_gui_component::compute_continuous_position(const bool x_axis, float discrete_position, const double range)
{
  discrete_position = x_axis ? discrete_position : discrete_position * -1.0f;

  float relative_position = 0.0f;
  float lower_bound = range / -2.0f;
  float upper_bound = range / 2.0f;

  if (discrete_position <= lower_bound) {
      relative_position = 0.0f;
  } else if (discrete_position >= upper_bound) {
      relative_position = 1.0f;
  } else {
      relative_position = (0.5 / upper_bound) * discrete_position + 0.5;
  }

  return relative_position;
}
