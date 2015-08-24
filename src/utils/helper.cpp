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

//C++ Libs
#include <cmath>
#include <string>
#include <algorithm>
#include <stdexcept>

//Own Libs
#include <src/utils/helper.h>

float SSR::helper::linear_to_dB(const float linear_value) { return 20.0f * std::log10(linear_value); }

float SSR::helper::dB_to_linear(const float dB_value) { return std::pow(10.0f, dB_value / 20.0f); }

std::string SSR::helper::get_environment_variable(const std::string& env_variable_name) {

  //environment variable name must be a string with '\0' termination
  char* val = std::getenv(env_variable_name.c_str());

  if (val == NULL) {
      throw std::invalid_argument("The Environment Variable " + env_variable_name + " is not known!");
  }

  return val;
}
