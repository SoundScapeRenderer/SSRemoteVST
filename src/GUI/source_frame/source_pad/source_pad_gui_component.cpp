#include <src/GUI/source_frame/source_pad/source_pad_gui_component.h>

SSR::Source_pad_gui_component::Source_pad_gui_component(int width, int heigth)
: Component("GUI_component_source_pad")
, grid(nullptr)
, source(new SSR::Source_gui_component())
, scale_reference(new SSR::Scale_reference_GUI_component(width, 5))
, current_absolute_x_position(0.0f)
, current_absolute_y_position(0.0f)
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
  grid =                nullptr;
  source =              nullptr;
  scale_reference =     nullptr;
}

void SSR::Source_pad_gui_component::move_source(const float absolute_x_position, const float absolute_y_position, const double range)
{
  current_absolute_x_position = absolute_x_position;
  current_absolute_y_position = absolute_y_position;
  move_source_relative(compute_relative_position(true, absolute_x_position, range), compute_relative_position(false, absolute_y_position, range));
}

void SSR::Source_pad_gui_component::update_range(const double range)
{
  move_source_relative(compute_relative_position(true, current_absolute_x_position, range), compute_relative_position(false, current_absolute_y_position, range));
}

void SSR::Source_pad_gui_component::set_reference_range(const double new_reference_range)
{
  scale_reference->set_reference_range(new_reference_range);
}

/**
 * PRIVATE
 */

void SSR::Source_pad_gui_component::move_source_relative(const float absolute_x_position, const float absolute_y_position)
{
  float concrete_x = absolute_x_position * getWidth() - source->get_radius();
  concrete_x = concrete_x < 0.0f ? 0.0f : concrete_x;
  concrete_x = concrete_x > getWidth() - source->getWidth() ? getWidth() - source->getWidth() : concrete_x;

  float concrete_y = absolute_y_position * getWidth() - source->get_radius();
  concrete_y = concrete_y < 0.0f ? 0.0f : concrete_y;
  concrete_y = concrete_y > getHeight() - source->getHeight() ? getHeight() - source->getHeight() : concrete_y;

  source->setBounds(concrete_x, concrete_y, source->getWidth(), source->getHeight());
  source->repaint();
}

float SSR::Source_pad_gui_component::compute_relative_position(const bool x_axis, float position, const double range)
{
  position = x_axis ? position : position * -1.0f;

  float relative_position = 0.0f;
  float lower_bound = range / -2.0f;
  float upper_bound = range / 2.0f;

  if (position <= lower_bound) {
      relative_position = 0.0f;
  } else if (position >= upper_bound) {
      relative_position = 1.0f;
  } else {
      relative_position = (0.5 / upper_bound) * position + 0.5;
  }

  return relative_position;
}
