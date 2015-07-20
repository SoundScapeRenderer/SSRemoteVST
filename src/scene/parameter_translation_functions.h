#ifndef PARAMETER_TRANSLATION_FUNCTIONS_H
#define PARAMETER_TRANSLATION_FUNCTIONS_H

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

namespace SSR
{

  namespace translations
  {

    /**
     * Computes the source continuous X position from discrete value and
     * returns the continuous value.
     *
     * This is made with the following linear function:
     *
     * f(x) = (0.5 / (range / 2)) * x + 0.5 { x || x >= (range / 2) & x <= (range / -2) }
     *
     * The function will return 0.0 if the position is less or equal range / -2
     * and 1.0 if the position is greater or equal range / 2.
     *
     * @param           discrete_position       The discrete position.
     *
     * @param           scene_range             The scene range.
     *
     * @return          0.0 if the position is less or equal range / -2, 1.0
     *                  if the position is greater or equal range / 2, otherwise
     *                  the result of the above written function f.
     */
    float x_position_discrete_to_continuous(float discrete_position, double scene_range);

    /**
     * Computes the discrete source X position from a continuous value (0.0 to 1.0) and
     * returns the discrete value.
     *
     * This is made with the following linear function:
     *
     * f(x) = range * x - range/2 { x || x >= 0.0 & x <= 1.0 }
     *
     * The function will return the minimum or maximum value of the current
     * range if the value is greater than 1.0 or less than 0.0.
     *
     * @param           continuous_position     The continuous position.
     *
     * @param           scene_range             The scene range.
     *
     * @return           the minimum or maximum value of the current
     *                   range if the value is greater than 1.0 or less than
     *                   0.0 else the result of the above written function f.
     */
    float x_position_continuous_to_discrete(float continuous_position, double scene_range);

    /**
     * Computes the source continuous Y position from discrete value and
     * returns the continuous value.
     *
     * This is made with the following linear function:
     *
     * f(x) = (0.5 / (range / 2)) * (x * -1) + 0.5 { x || x >= (range / 2) & x <= (range / -2)
     *
     * The function will return 0.0 if the position is less or equal range / -2
     * and 1.0 if the position is greater or equal range / 2.
     *
     * @param           discrete_position       The discrete position.
     *
     * @param           scene_range             The scene range.
     *
     * @return          0.0 if the position is less or equal range / -2, 1.0
     *                  if the position is greater or equal range / 2, otherwise
     *                  the result of the above written function f.
     */
    float y_position_discrete_to_continuous(float discrete_position, double scene_range);

    float y_position_continuous_to_discrete(float continuous_position, double scene_range);

    float gain_discrete_to_continuous(float discrete_linear_gain);
    float gain_continuous_to_discrete(float continuous_linear_gain);

    float orientation_discrete_to_continuous(float discrete_orientation);
    float orientation_continuous_to_discrete(float continuous_orientation);

    float mute_discrete_to_continuous(bool discrete_mute);
    bool mute_continuous_to_discrete(float continuous_mute);

    float model_point_discrete_to_continuous(bool discrete_model);
    bool model_point_continuous_to_discrete(float continuous_model);
    
    float fixed_discrete_to_continuous(bool discrete_fixed);
    bool fixed_continuous_to_discrete(float continuous_fixed);

  }


}

#endif
