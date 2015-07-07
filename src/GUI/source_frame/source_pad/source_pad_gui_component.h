#ifndef SOURCE_PAD_GUI_COMPONENT_H
#define SOURCE_PAD_GUI_COMPONENT_H

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
#include <src/JuceHeader.h>

//C++ Libs
#include <memory>

//Own Libs
#include <src/GUI/source_frame/source_pad/grid_gui_component.h>
#include <src/GUI/source_frame/source_pad/source_gui_component.h>
#include <src/GUI/source_frame/source_pad/scale_reference_gui_component.h>

namespace SSR
{

  class Source_pad_gui_component : public juce::Component
  {

  public:

    Source_pad_gui_component(int width, int heigth);

    ~Source_pad_gui_component();

    void move_source(const float absolute_x_position, const float absolute_y_position, const double range);

    void update_range(const double range);

    void set_reference_range(const double new_reference_range);

  private:
    void move_source_relative(const float absolute_x_position, const float absolute_y_position);
    float compute_relative_position(const bool x_axis, float position, const double range);

  private:
    float current_absolute_x_position;
    float current_absolute_y_position;
    std::unique_ptr<SSR::Grid_gui_component> grid;
    std::unique_ptr<SSR::Source_gui_component> source;
    std::unique_ptr<SSR::Scale_reference_GUI_component> scale_reference;

  };

}

#endif
