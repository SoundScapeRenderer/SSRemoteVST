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

  /**
   * This file contains functions to translate discrete to continuous values
   * and continuous to discrete values.
   *
   * The need for the translation functions is caused by the VST automation
   * interface. The VST automation interface represents and stores all
   * parameters as continuous values (from 0.0 to 1.0). The SSRemote VST
   * therefore stores all parameters as discrete and continuous values.
   *
   * @since 2015-07-21
   * @author Florian Willich
   */
  namespace translations
  {

    /**
     * Computes the source continuous X position from discrete value and
     * returns the continuous value.
     *
     * The following linear function was used for this purpose:
     *
     * x = discrete_position
     * f(x) = (0.5 / (range/2)) * x + 0.5 { x || x > (range / 2) & x < (range / -2) }
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
     *
     * @author Florian Willich
     */
    float x_position_discrete_to_continuous(float discrete_position, double scene_range);

    /**
     * Computes the discrete source X position from the continuous X position
     * (0.0 to 1.0) and returns the discrete value.
     *
     * The following linear function was used for this purpose:
     *
     * x = continuous_position
     * f(x) = range * x - range/2 { x || x > 0.0 & x < 1.0 }
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
     *
     * @author Florian Willich
     */
    float x_position_continuous_to_discrete(float continuous_position, double scene_range);

    /**
     * Computes the source continuous Y position from discrete value and
     * returns the continuous value.
     *
     * The following linear function was used for this purpose:
     *
     * x = discrete_position
     * f(x) = (0.5 / (range/2)) * (-x) + 0.5 { x || x > (range / 2) & x < (range / -2)
     *
     * The function will return 0.0 if the position is less or equal range / -2
     * and 1.0 if the position is greater or equal range / 2.
     *
     * @param           discrete_position       The discrete Y position.
     *
     * @param           scene_range             The scene range.
     *
     * @return          0.0 if the position is less or equal range / -2, 1.0
     *                  if the position is greater or equal range / 2, otherwise
     *                  the result of the above written function f.
     *
     * @author Florian Willich
     */
    float y_position_discrete_to_continuous(float discrete_position, double scene_range);

    /**
     * Computes the discrete source Y position from the continuous Y position
     * (0.0 to 1.0) and returns the discrete value.
     *
     * The following linear function was used for this purpose:
     *
     * x = continuous_position
     * f(x) = -(range * x - range/2) { x || x > 0.0 & x < 1.0 }
     *
     * The function will return the minimum or maximum value of the current
     * range if the value is greater equal 1.0 or less equal 0.0. Otherwise, the
     * function will return the result of the above written function f.
     *
     * @param           continuous_position     The continuous Y position.
     *
     * @param           scene_range             The scene range.
     *
     * @return the minimum or maximum value of the current range if the value
     *         is greater equal 1.0 or less equal 0.0 else the result of the
     *         above written function f.
     *
     * @author Florian Willich
     */
    float y_position_continuous_to_discrete(float continuous_position, double scene_range);

    /**
     * Computes the continuous linear gain from the discrete linear gain
     * (0.0 to 1.0).
     *
     * @param           discrete_linear_gain    The discrete linear gain.
     *
     * @return the continuous linear gain.
     *
     * @author Florian Willich
     */
    float gain_discrete_to_continuous(float discrete_linear_gain);

    /**
     * Computes the discrete linear gain from the continuouos linear gain.
     *
     * @param           continuous_linear_gain  The conitnuous linear gain.
     *
     * @return the discrete linear gain from the continuouos linear gain.
     *
     * @author Florian Willich
     */
    float gain_continuous_to_discrete(float continuous_linear_gain);

    /**
     * Computes the continuous orientation from the discrete orientation.
     *
     * The following function was used for this purpose:
     *
     * x = discrete_orientation
     * f(x) = x / (2*pi)
     *
     * @param           discrete_orientation    The discrete orientation.
     *
     * @return the result of the above written function f (max 1.0, min 0.0).
     *
     * @author Florian Willich
     */
    float orientation_discrete_to_continuous(float discrete_orientation);

    /**
     * Computes the discrete orientation from the continuous orientation.
     *
     * The following function was used for this purpose:
     *
     * x = continuous_orientation
     * f(x) = (x * 2*pi) % 2*pi
     *
     * @param           continuous_orientation  The continuous orientation.
     *
     * @return the result of the above written function f.
     *
     * @author Florian Willich
     */
    float orientation_continuous_to_discrete(float continuous_orientation);

    /**
     * Computes the continuous mute value from the discrete mute value as
     * follows:
     *
     * If discrete_mute is true the function returns 1.0, otherwise 0.0.
     *
     * @param           discrete_mute           The discrete mute value.
     *
     * @return 1.0f if discrete_mute is true, otherwise 0.0.
     *
     * @author Florian Willich
     */
    float mute_discrete_to_continuous(bool discrete_mute);

    /**
     * Computes the discrete mute value from the continuous mute value as
     * follows:
     *
     * If continuous_mute is 1.0 the function returns true, false otherwise.
     *
     * @param           continuous_mute         The continuous mute value.
     *
     * @return true if continuous_mute is 1.0, false otherwise.
     */
    bool mute_continuous_to_discrete(float continuous_mute);

    /**
     * Computes the continuous model point value from the discrete model point
     * value as follows:
     *
     * If discrete_model is true the function returns 1.0, otherwise 0.0.
     *
     * @param           discrete_model           The discrete model value.
     *
     * @return 1.0f if discrete_model is true, otherwise 0.0.
     *
     * @author Florian Willich
     */
    float model_point_discrete_to_continuous(bool discrete_model);

    /**
     * Computes the discrete model point value from the continuous model point
     * value as follows:
     *
     * If continuous_model is 1.0 the function returns true, false otherwise.
     *
     * @param           continuous_model         The continuous model value.
     *
     * @return true if continuous_model is 1.0, false otherwise.
     */
    bool model_point_continuous_to_discrete(float continuous_model);

    /**
     * Computes the continuous fixed value from the discrete fixed
     * value as follows:
     *
     * If discrete_fixed is true the function returns 1.0, otherwise 0.0.
     *
     * @param           discrete_fixed           The discrete fixed value.
     *
     * @return 1.0f if discrete_fixed is true, otherwise 0.0.
     *
     * @author Florian Willich
     */
    float fixed_discrete_to_continuous(bool discrete_fixed);

    /**
     * Computes the discrete fixed value from the continuous fixed value as
     * follows:
     *
     * If continuous_fixed is 1.0 the function returns true, false otherwise.
     *
     * @param           continuous_fixed         The continuous fixed value.
     *
     * @return true if continuous_fixed is 1.0, false otherwise.
     */
    bool fixed_continuous_to_discrete(float continuous_fixed);

  }


}

#endif
