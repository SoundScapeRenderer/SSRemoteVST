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
#include <string>
#include <sstream>

//Own classes
#include <src/utils/ssr_requester.h>
#include <src/utils/helper.h>

//++++++++++++++++++++++++++++++++++++
// PUBLIC ++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++

SSR::SSR_requester::SSR_requester() : request_ss(new std::stringstream(std::string())) { }

SSR::SSR_requester::~SSR_requester() { delete request_ss; }

const std::string SSR::SSR_requester::build(Build_function bf)
{
  request_ss->str(std::string());

  *request_ss << "<request>";

  bf(request_ss);

  *request_ss << "</request>";

  return request_ss->str();
}

void SSR::request::source_position(std::ostream* output, const float source_id, const float x, const float y)
{
  *output << "<source id=\"" << source_id << "\"><position x=\"" << x << "\" y=\"" << y << "\"/></source>";
}

void SSR::request::source_gain(std::ostream* output, const float source_id, const float gain_in_db)
{
  *output << "<source id=\"" << source_id << "\" volume=\"" << gain_in_db << "\"/>";
}

void SSR::request::source_mute(std::ostream* output, const int source_id, const bool mute) 
{   
  *output << "<source id=\"" << source_id << "\" mute=\"" << mute << "\"/>";
}

void SSR::request::source_fixed(std::ostream* output, const int source_id, const bool fixed)
{
  *output << "<source id=\"" << source_id << "\"><position fixed=\"" << fixed << "\"/></source>";
}

void SSR::request::source_model(std::ostream* output, const int source_id, const std::string model)
{
  *output << "<source id=\"" << source_id << "\" model=\"" << model << "\"/>";
}

void SSR::request::source_name(std::ostream* output, const int source_id, const std::string name)
{
  *output << "<source id=\"" << source_id << "\" name=\"" << name << "\"/>";
}

void SSR::request::source_properties_file(std::ostream* output, const int source_id, const std::string properties_file)
{
  *output << "<source id=\"" << source_id << "\" properties_file=\"" << properties_file << "\"/>";
}

void SSR::request::source_port(std::ostream* output, const int source_id, const std::string port)
{
  *output << "<source id=\"" << source_id << "\" port=\"" << port << "\"/>";
}

void SSR::request::new_source(std::ostream* output, const std::string name, const std::string port, const float x_position, const float y_position)
{
  *output << "<source new=\"true\" name=\"" << name << "\" port=\"" << port << "\"><position x=\"" << x_position << "\" y=\"" << y_position << "\"/></source>";
}
