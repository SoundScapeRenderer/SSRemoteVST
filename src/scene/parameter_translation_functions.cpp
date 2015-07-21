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
#include <algorithm>

//Boost Libs
#include <boost/math/constants/constants.hpp>

float SSR::translations::x_position_discrete_to_continuous(float discrete_position, double scene_range)
{
  float relative_position = 0.0f;
  float lower_bound = scene_range / -2.0f;
  float upper_bound = scene_range / 2.0f;

  if (discrete_position <= lower_bound) {
      relative_position = 0.0f;
  } else if (discrete_position >= upper_bound) {
      relative_position = 1.0f;
  } else {
      relative_position = (0.5 / upper_bound) * discrete_position + 0.5;
  }

  return relative_position;
}

float SSR::translations::x_position_continuous_to_discrete(float continuous_position, double scene_range)
{
  float discrete_position = 0.0f;
  float margin = scene_range / 2.0f;

  if (continuous_position >= 1.0f) {
      discrete_position = margin;
  } else if (continuous_position <= 0.0f) {
      discrete_position = margin * -1.0f;
  } else {
      discrete_position = scene_range * continuous_position - margin;
  }

  return discrete_position;
}

float SSR::translations::y_position_discrete_to_continuous(float discrete_position, double scene_range)
{
  discrete_position *= -1.0f;

  float continuous_position = 0.0f;
  float lower_bound = scene_range / -2.0f;
  float upper_bound = scene_range / 2.0f;

  if (discrete_position <= lower_bound) {
      continuous_position = 0.0f;
  } else if (discrete_position >= upper_bound) {
      continuous_position = 1.0f;
  } else {
      continuous_position = (0.5 / upper_bound) * discrete_position + 0.5;
  }

  return continuous_position;
}

float SSR::translations::y_position_continuous_to_discrete(float continuous_position, double scene_range)
{
  float discrete_position = 0.0f;
  float margin = scene_range / 2.0f;

  if (continuous_position >= 1.0f) {
      discrete_position = margin;
  } else if (continuous_position <= 0.0f) {
      discrete_position = margin * -1.0f;
  } else {
      discrete_position = scene_range * continuous_position - margin;
  }

  return discrete_position * -1.0f;
}

float SSR::translations::gain_discrete_to_continuous(float discrete_linear_gain)
{
  float continuous_value = discrete_linear_gain / 4.0f;

  continuous_value = std::min(continuous_value, 1.0f);
  continuous_value = std::max(continuous_value, 0.0f);

  return continuous_value;
}

float SSR::translations::gain_continuous_to_discrete(float continuous_linear_gain)
{
  return continuous_linear_gain * 4.0f;
}

float SSR::translations::orientation_discrete_to_continuous(float discrete_orientation)
{
  float continuous_orientation = discrete_orientation / (2 *  boost::math::float_constants::pi);

  continuous_orientation = std::min(continuous_orientation, 1.0f);
  continuous_orientation = std::max(continuous_orientation, 0.0f);

  return continuous_orientation;
}

float SSR::translations::orientation_continuous_to_discrete(float continuous_orientation)
{
  float discrete_orientation = continuous_orientation * 2 * boost::math::float_constants::pi;
  discrete_orientation = std::fmod(discrete_orientation, 2 * boost::math::float_constants::pi);

  return discrete_orientation;
}

float SSR::translations::mute_discrete_to_continuous(bool discrete_mute)
{
  return discrete_mute ? 1.0f : 0.0f;
}

bool SSR::translations::mute_continuous_to_discrete(float continuous_mute)
{
  return continuous_mute == 1.0f;
}

float SSR::translations::model_point_discrete_to_continuous(bool discrete_model)
{
  return discrete_model ? 1.0f : 0.0f;
}

bool SSR::translations::model_point_continuous_to_discrete(float continuous_model)
{
  return continuous_model == 1.0f;
}

float SSR::translations::fixed_discrete_to_continuous(bool discrete_fixed)
{
  return discrete_fixed ? 1.0f : 0.0f;
}

bool SSR::translations::fixed_continuous_to_discrete(float continuous_fixed)
{
  return continuous_fixed == 1.0f;
}
