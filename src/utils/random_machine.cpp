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

#include <src/utils/random_machine.h>

#include <memory>
#include <random>
#include <sstream>

unsigned int SSR::Random_machine::operator()() const
{
  return (*random_device)();
}

unsigned int SSR::Random_machine::generate() const
{
  return (*random_device)();
}

unsigned int SSR::Random_machine::generate_unsigned_int(const unsigned int lower_bound, const unsigned int upper_bound) const
{
  return lower_bound + generate() % (upper_bound - lower_bound + 1);
}

char SSR::Random_machine::generate_char(const char lower_bound, const char upper_bound) const
{
  return static_cast<char>(lower_bound + generate() % (upper_bound - lower_bound + 1));
}

std::string SSR::Random_machine::generate_string(const std::size_t length, const char lower_bound, const char upper_bound) const
{
  std::stringstream ss;

  for (unsigned int i = 0; i < length; i++) {
      ss << generate_char(lower_bound, upper_bound);
  }

  return ss.str();
}

int SSR::Random_machine::generate_int(const int lower_bound, const int upper_bound) const
{
  return lower_bound + generate() % (upper_bound - lower_bound + 1);
}

float SSR::Random_machine::generate_float(const float lower_bound, const float upper_bound) const
{
  unsigned int x = generate();
  float a = ((upper_bound + (-lower_bound)) / get_maximum());
  float b = lower_bound;
  return  a * x + b;
}

double SSR::Random_machine::generate_double(const double lower_bound, const double upper_bound) const
{
  unsigned int x = generate();
  double a = ((upper_bound + (-lower_bound)) / get_maximum());
  double b = lower_bound;
  return  a * x + b;
}

unsigned int SSR::Random_machine::get_minimum() const
{
  return random_device->min();
}

unsigned int SSR::Random_machine::get_maximum() const
{
  return random_device->max();
}

SSR::Random_machine::~Random_machine()
{

}

SSR::Random_machine::Random_machine()
: random_device(new std::random_device())
{

}
