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

#include <src/scene/source.h>

//C++ Libs
#include <memory>
#include <string>
#include <functional>

//Own Libs
#include <src/utils/helper.h>
#include <src/utils/random_machine.h>
#include <src/parameter/parameter.h>
#include <src/scene/parameter_translation_functions.h>

SSR::Source::Source(const unsigned int id, const std::string name, float scene_range)
: id(id)
, x_position(   0.0f,
                0.0f,
                std::bind(SSR::translations::x_position_discrete_to_continuous, std::placeholders::_1, scene_range),
                std::bind(SSR::translations::x_position_continuous_to_discrete, std::placeholders::_1, scene_range),
                "X Position")
, y_position(   0.0f,
                0.0f,
                std::bind(SSR::translations::y_position_discrete_to_continuous, std::placeholders::_1, scene_range),
                std::bind(SSR::translations::y_position_continuous_to_discrete, std::placeholders::_1, scene_range),
                "Y Position")
, gain(         1.0f,
                1.0f,
                SSR::translations::gain_discrete_to_continuous,
                SSR::translations::gain_continuous_to_discrete,
                "Gain")
, orientation(  0.0f,
                0.0f,
                SSR::translations::orientation_discrete_to_continuous,
                SSR::translations::orientation_continuous_to_discrete,
                "Orientation")
, mute(         false,
                false,
                SSR::translations::mute_discrete_to_continuous,
                SSR::translations::mute_continuous_to_discrete,
                "Mute")
, model_point(  true,
                true,
                SSR::translations::model_point_discrete_to_continuous,
                SSR::translations::model_point_continuous_to_discrete,
                "Model")
, fixed(        false,
                false,
                SSR::translations::fixed_discrete_to_continuous,
                SSR::translations::fixed_continuous_to_discrete,
                "Fixed")
, name(name)
, properties_file("")
, jackport("capture_2")
{
  set_all_parameters_on_default();
  auto random_machine = SSR::Random_machine::get_instance();
  x_position.set_discrete_value(random_machine->generate_float(-1.0f, 1.0f));
  y_position.set_discrete_value(random_machine->generate_float(-1.0f, 1.0f));
}

SSR::Source::Source(const unsigned int id, const std::string name, float scene_range, const std::string jackport)
: Source(id, name, scene_range)
{
  this->jackport = jackport;
}

SSR::Source::Source(const SSR::Source& other)
: id(other.id)
, x_position(other.x_position)
, y_position(other.y_position)
, gain(other.gain)
, orientation(other.orientation)
, mute(other.mute)
, model_point(other.model_point)
, fixed(other.fixed)
, name(other.name)
, properties_file(other.properties_file)
, jackport(other.jackport)
{

}

SSR::Source& SSR::Source::operator=(const SSR::Source& other)
{

  if (*this != other) {
    SSR::Source tmp(other);
    swap(*this, tmp);
  }

  return *this;
}

void SSR::Source::swap(SSR::Source& first, SSR::Source& second)
{
  std::swap(first.id,                   second.id);
  std::swap(first.x_position,           second.x_position);
  std::swap(first.y_position,           second.y_position);
  std::swap(first.gain,                 second.gain);
  std::swap(first.orientation,          second.orientation);
  std::swap(first.mute,                 second.mute);
  std::swap(first.model_point,          second.model_point);
  std::swap(first.fixed,                second.fixed);
  std::swap(first.name,                 second.name);
  std::swap(first.properties_file,      second.properties_file);
  std::swap(first.jackport,             second.jackport);
}

SSR::Source::~Source()
{

}

void SSR::Source::set_x_position_discrete(const float position)
{
  x_position.set_discrete_value(position);
}

SSR::Parameter<float, float> SSR::Source::get_x_position() const
{
  return x_position;
}

void SSR::Source::set_x_position_continuous(const float position)
{
  x_position.set_continuous_value(position);
}

void SSR::Source::set_y_position_discrete(const float position)
{
  y_position.set_discrete_value(position);
}

SSR::Parameter<float, float> SSR::Source::get_y_position() const
{
  return y_position;
}

void SSR::Source::set_y_position_continuous(const float new_relative_position)
{
  y_position.set_continuous_value(new_relative_position);
}

void SSR::Source::set_discrete_gain(const float gain_value, const bool linear)
{

  if (linear) {
      gain.set_discrete_value(gain_value);
  } else {
      float linear_value = SSR::helper::dB_to_linear(gain_value);
      gain.set_discrete_value(linear_value);
  }

}

void SSR::Source::set_continuous_gain(const float gain_value)
{
  gain.set_continuous_value(gain_value);
}

SSR::Parameter<float, float> SSR::Source::get_gain() const
{
  return gain;
}

void SSR::Source::set_id(const unsigned int new_id)
{
  id = new_id;
}

unsigned int SSR::Source::get_id() const
{
  return id;
}

void SSR::Source::set_discrete_orientation(const float discrete_orientation)
{
  orientation.set_discrete_value(discrete_orientation);
}

void SSR::Source::set_continuous_orientation(const float continuous_orientation)
{
  orientation.set_continuous_value(continuous_orientation);
}

SSR::Parameter<float, float> SSR::Source::get_orientation() const
{
  return orientation;
}

void SSR::Source::set_discrete_mute(const bool discrete_mute)
{
  mute.set_discrete_value(discrete_mute);
}

void SSR::Source::set_continuous_mute(const float continuous_mute)
{
  mute.set_continuous_value(continuous_mute);
}

SSR::Parameter<bool, float> SSR::Source::get_mute() const
{
  return mute;
}

void SSR::Source::set_discrete_model_point(const bool point)
{
  model_point.set_discrete_value(point);
}

void SSR::Source::set_continuous_model_point(const float point)
{
  model_point.set_continuous_value(point);
}

SSR::Parameter<bool, float> SSR::Source::get_model_point() const
{
  return model_point;
}

void SSR::Source::set_discrete_fixed(const bool fixed_value)
{
  fixed.set_discrete_value(fixed_value);
}

void SSR::Source::set_continuous_fixed(const float fixed_value)
{
  fixed.set_continuous_value(fixed_value);
}

SSR::Parameter<bool, float> SSR::Source::get_fixed() const
{
  return fixed;
}

void SSR::Source::set_name(const std::string new_name)
{
  name = new_name;
}

std::string SSR::Source::get_name() const
{
  return name;
}

void SSR::Source::set_properties_file(const std::string name)
{
  properties_file = name;
}

std::string SSR::Source::get_properties_file() const
{
  return properties_file;
}

void SSR::Source::set_jackport(const std::string name)
{
  jackport = name;
}

std::string SSR::Source::get_jackport() const
{
  return jackport;
}

void SSR::Source::set_all_parameters_on_default()
{
  x_position.set_to_default();
  y_position.set_to_default();
  gain.set_to_default();
  orientation.set_to_default();
  mute.set_to_default();
  model_point.set_to_default();
  fixed.set_to_default();
}

bool operator==(const SSR::Source& lhs, const SSR::Source& rhs)
{
  bool is_equal = true;

  is_equal = is_equal ? lhs.get_x_position()            == rhs.get_x_position()         : false;
  is_equal = is_equal ? lhs.get_y_position()            == rhs.get_y_position()         : false;
  is_equal = is_equal ? lhs.get_gain()                  == rhs.get_gain()               : false;
  is_equal = is_equal ? lhs.get_orientation()           == rhs.get_orientation()        : false;
  is_equal = is_equal ? lhs.get_mute()                  == rhs.get_mute()               : false;
  is_equal = is_equal ? lhs.get_model_point()           == rhs.get_model_point()        : false;
  is_equal = is_equal ? lhs.get_fixed()                 == rhs.get_fixed()              : false;
  is_equal = is_equal ? lhs.get_id()                    == rhs.get_id()                 : false;
  is_equal = is_equal ? lhs.get_name()                  == rhs.get_name()               : false;
  is_equal = is_equal ? lhs.get_jackport()              == rhs.get_jackport()           : false;
  is_equal = is_equal ? lhs.get_properties_file()       == rhs.get_properties_file()    : false;

  return is_equal;
}

bool operator!=(const SSR::Source& lhs, const SSR::Source& rhs)
{
  return !(lhs == rhs);
}

void std::swap(SSR::Source& first, SSR::Source& second)
{
  SSR::Source tmp(first);
  first = second;
  second = tmp;
}
