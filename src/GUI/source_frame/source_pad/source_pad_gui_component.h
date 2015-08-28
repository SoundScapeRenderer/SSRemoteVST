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
#include <JUCE/JuceHeader.h>

//C++ Libs
#include <memory>

//Own Libs
#include <src/GUI/source_frame/source_pad/grid_gui_component.h>
#include <src/GUI/source_frame/source_pad/source_gui_component.h>
#include <src/GUI/source_frame/source_pad/scale_reference_gui_component.h>

namespace SSR
{

  /**
   * This class represents the 'Source pad GUI component' including a grid,
   * the source that moves on the grid and a scale reference to visualize
   * the scale of the grid.
   */
  class Source_pad_gui_component
      : public juce::Component
  {

  public:

    /**
     * Constructor initialising and configuring all related components.
     *
     * Sets the size of this GUI component to the transferred width and heigth.
     *
     * @param   width           The width in pixels this GUI component shall
     *                          have.
     *
     * @param   heigth          The heigth in pixels this GUI component shall
     *                          have.
     */
    Source_pad_gui_component(int width, int heigth);

    /**
     * Destructor.
     */
    ~Source_pad_gui_component();

    /**
     * Moves the sources X and Y position to the transferred discrete_x_position
     * and discrete_y_position.
     *
     * @param   discrete_x_position     The discrete X position the source shall
     *                                  be moved to.
     *
     * @param   discrete_y_position     The discrete Y position the source shall
     *                                  be moved to.
     *
     * @param   range                   The range of the grid.
     */
    void move_source(const float discrete_x_position, const float discrete_y_position, const double range);

    /**
     * Updates the range of the grid and computes the new position the source
     * will be placed in the grid (this is not changing the position of the
     * source just the visual representation).
     *
     * @param   range                   The new range of the grid.
     */
    void update_range(const double range);

    /**
     * Sets the range the scale reference is referring to to the new_reference_range.
     *
     * @param   new_reference_range     The new range the scale reference component
     *                                  shall refer to.
     */
    void set_reference_range(const double new_reference_range);

  private:

    /**
     * Moves the source to the new X and Y position defined by the continuous
     * values continuous_x_position and continuous_y_position.
     *
     * If the resulting discrete positions are less than 0.0 the new positions
     * will be assigned to 0.0.
     *
     * @param   continuous_x_position   The new continuous X position the source
     *                                  shall be moved to (from 0.0 to 1.0).
     *
     * @param   continuous_y_position   The new continuous Y position the source
     *                                  shall be moved to (from 0.0 to 1.0).
     */
    void move_source_continuously(const float continuous_x_position, const float continuous_y_position);

    /**
     * Computes the continuous position of the source using the transferred
     * discrete_position and the transferred range and returns the result.
     *
     * The transferred x_axis boolean value defines if the continuous position
     * shall be computed for the X axis (true) or the Y axis (false).
     *
     * @param   x_axis                  Defines if the continuous position
     *                                  shall be computed for the X axis (true)
     *                                  or the Y axis (false).
     *
     * @param   discrete_position       The discrete position of the source.
     *
     * @param   range                   The range for which the continuous
     *                                  position shall be computed.
     */
    float compute_continuous_position(const bool x_axis, float discrete_position, const double range);

  private:

    /**
     * The current discrete X position of the source.
     */
    float current_discrete_x_position;

    /**
     * The current discrete Y position of the source.
     */
    float current_discrete_y_position;

    /**
     * The grid on which the source moves on.
     */
    std::unique_ptr<SSR::Grid_gui_component> grid;

    /**
     * The source.
     */
    std::unique_ptr<SSR::Source_gui_component> source;

    /**
     * The scale reference.
     */
    std::unique_ptr<SSR::Scale_reference_GUI_component> scale_reference;

  };

}

#endif
