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

#include <src/scene/parameter_translation_functions.h>

//C++ Libs
#include <cmath>

//Boost Libs
#include <boost/math/constants/constants.hpp>

float SSR::translations::x_position_discrete_to_continuous(float absolute_position, double scene_range)
{
  float relative_position = 0.0f;
  float lower_bound = scene_range / -2.0f;
  float upper_bound = scene_range / 2.0f;

  if (absolute_position <= lower_bound) {
      relative_position = 0.0f;
  } else if (absolute_position >= upper_bound) {
      relative_position = 1.0f;
  } else {
      relative_position = (0.5 / upper_bound) * absolute_position + 0.5;
  }

  return relative_position;
}

float SSR::translations::x_position_continuous_to_discrete(float relative_position, double scene_range)
{
  float absolute_position = 0.0f;
  float margin = scene_range / 2.0f;

  if (relative_position >= 1.0f) {
      absolute_position = margin;
  } else if (relative_position <= 0.0f) {
      absolute_position = margin * -1.0f;
  } else {
      absolute_position = scene_range * relative_position - margin;
  }

  return absolute_position;
}

float SSR::translations::y_position_discrete_to_continuous(float absolute_position, double scene_range)
{
  absolute_position *= -1.0f;

  float relative_position = 0.0f;
  float lower_bound = scene_range / -2.0f;
  float upper_bound = scene_range / 2.0f;

  if (absolute_position <= lower_bound) {
      relative_position = 0.0f;
  } else if (absolute_position >= upper_bound) {
      relative_position = 1.0f;
  } else {
      relative_position = (0.5 / upper_bound) * absolute_position + 0.5;
  }

  return relative_position;
}

float SSR::translations::y_position_continuous_to_discrete(float relative_position, double scene_range)
{
  float absolute_position = 0.0f;
  float margin = scene_range / 2.0f;

  if (relative_position >= 1.0f) {
      absolute_position = margin;
  } else if (relative_position <= 0.0f) {
      absolute_position = margin * -1.0f;
  } else {
      absolute_position = scene_range * relative_position - margin;
  }

  return absolute_position * -1.0f;
}

float SSR::translations::gain_discrete_to_continuous(float absolute_linear_gain)
{
  float relative_value = absolute_linear_gain / 4.0f;
  relative_value = relative_value > 1.0f ? 1.0f : relative_value;
  relative_value = relative_value < 0.0f ? 0.0f : relative_value;

  return relative_value;
}

float SSR::translations::gain_continuous_to_discrete(float relative_linear_gain)
{
  return relative_linear_gain * 4.0f;
}

float SSR::translations::orientation_discrete_to_continuous(float absolute_orientation)
{
  float relative_orientation = absolute_orientation / (2 *  boost::math::float_constants::pi);
  relative_orientation = relative_orientation > 1.0f ? 1.0f : relative_orientation;
  relative_orientation = relative_orientation < 0.0f ? 0.0f : relative_orientation;

  return relative_orientation;
}

float SSR::translations::orientation_continuous_to_discrete(float relative_orientation)
{
  float absolute_orientation = relative_orientation * 2 * boost::math::float_constants::pi;
  absolute_orientation = std::fmod(absolute_orientation, 2 * boost::math::float_constants::pi);

  return absolute_orientation;
}

float SSR::translations::mute_discrete_to_continuous(bool absolute_mute)
{
  return absolute_mute ? 1.0f : 0.0f;
}

bool SSR::translations::mute_continuous_to_discrete(float relative_mute)
{
  return relative_mute == 1.0f;
}

float SSR::translations::model_point_discrete_to_continuous(bool absolute_model)
{
  return absolute_model ? 1.0f : 0.0f;
}

bool SSR::translations::model_point_continuous_to_discrete(float relative_model)
{
  return relative_model == 1.0f;
}

float SSR::translations::fixed_discrete_to_continuous(bool absolute_fixed)
{
  return absolute_fixed ? 1.0f : 0.0f;
}

bool SSR::translations::fixed_continuous_to_discrete(float relative_fixed)
{
  return relative_fixed == 1.0f;
}
