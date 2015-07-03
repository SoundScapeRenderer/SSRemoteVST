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

#include <src/scene/scene.h>

//C++ Libs
#include <memory>
#include <vector>
#include <algorithm>

//Own Libs
#include <src/scene/source.h>
#include <src/parameter/parameter.h>

#include <JuceLibraryCode/JuceHeader.h>

typedef std::vector<SSR::Source>::iterator source_iterator;

SSR::Scene::Scene()
: sources(new std::vector<SSR::Source>())
, ids_and_names(new std::vector< std::pair<unsigned int, std::string> >())
, scene_range(2000.0)
, current_selected_source()
{
  new_source("Default Source");
}

SSR::Scene::~Scene()
{
  sources = nullptr;
}

void SSR::Scene::interpret_xml_message(std::string xml_message)
{

  XmlDocument xml_document(xml_message);
  auto main_element = std::unique_ptr<juce::XmlElement>(xml_document.getDocumentElement());

  if (main_element->hasTagName("update")) {

      forEachXmlChildElement (*main_element, e) {

        if (e->hasTagName("source")) {

            if (e->hasAttribute("id")) {

                int id = e->getIntAttribute("id");

                if (id_already_in_use(id)) {

                    manipulate_source(get_iterator(id), e);

                } else {

                    if (e->hasAttribute("name")) {

                        std::string name = e->getStringAttribute("name").toStdString();
                        sources->push_back(SSR::Source(id, name));
                        ids_and_names->push_back( std::pair<unsigned int, std::string>(id, name) );
                        current_selected_source = sources->begin();

                        manipulate_source(get_iterator(id), e);

                    }

                }

            }

         }

      }

      main_element->deleteAllChildElements();

  }

}

bool SSR::Scene::select_source(const int id)
{
  bool source_is_selected = false;

  for (source_iterator it = sources->begin(); it != sources->end(); it++) {

      if (it->get_id() == id) {
          current_selected_source = it;
          source_is_selected = true;
      }

  }

  return source_is_selected;
}

std::shared_ptr< std::vector< std::pair<unsigned int, std::string> > > SSR::Scene::get_source_ids_and_names()
{
  return ids_and_names;
}

SSR::Source SSR::Scene::get_source() const
{
  SSR::Source s = *current_selected_source;
  return s;
}

unsigned int SSR::Scene::new_source(const std::string name)
{
  unsigned int id = get_next_id();
  sources->push_back(SSR::Source(id, name));
  ids_and_names->push_back( std::pair<unsigned int, std::string>(id, name) );
  current_selected_source = get_iterator(id);
  return id;
}

bool SSR::Scene::new_source(const std::string name, const unsigned int id)
{
  bool source_successfully_created = false;

  if (!id_already_in_use(id)) {
      sources->push_back(SSR::Source(id, name));
      ids_and_names->push_back( std::pair<unsigned int, std::string>(id, name) );
      current_selected_source = get_iterator(id);
      source_successfully_created = true;
  }

  return source_successfully_created;
}

bool SSR::Scene::new_source(const std::string name, const unsigned int id, const std::string jackport)
{
  bool source_successfully_created = false;

  if (!id_already_in_use(id)) {
      sources->push_back(SSR::Source(id, name, jackport));
      ids_and_names->push_back( std::pair<unsigned int, std::string>(id, name) );
      current_selected_source = get_iterator(id);
      source_successfully_created = true;
  }

  return source_successfully_created;
}

void SSR::Scene::set_id_of_selected_source(const int id)
{
  set_id_of_source(current_selected_source->get_id(), id);
}

int SSR::Scene::get_id_of_selected_source() const
{
  return current_selected_source->get_id();
}

void SSR::Scene::set_x_position_absolute_of_selected_source(const float new_position)
{
  current_selected_source->set_x_position_absolute(new_position);
}


void SSR::Scene::set_x_position_relative_of_selected_source(const float new_position)
{
  current_selected_source->set_x_position_relative(new_position);
}

SSR::Parameter<float, float> SSR::Scene::get_x_position_of_selected_source() const
{
  return current_selected_source->get_x_position();
}

void SSR::Scene::set_y_position_absolute_of_selected_source(const float new_position)
{
  current_selected_source->set_y_position_absolute(new_position);
}

void SSR::Scene::set_y_position_relative_of_selected_source(const float new_position)
{
  current_selected_source->set_y_position_relative(new_position);
}

SSR::Parameter<float, float> SSR::Scene::get_y_position_of_selected_source() const
{
  return current_selected_source->get_y_position();
}

void SSR::Scene::set_gain_absolute_of_selected_source(const float value, const bool linear)
{
  current_selected_source->set_absolute_gain(value, linear);
}

void SSR::Scene::set_gain_relative_of_selected_source(const float new_gain)
{
  current_selected_source->set_relative_gain(new_gain);
}

SSR::Parameter<float, float> SSR::Scene::get_gain_of_selected_source() const
{
  return current_selected_source->get_gain();
}

void SSR::Scene::set_orientation_absolute_of_selected_source(const float value)
{
  current_selected_source->set_absolute_orientation(value);
}

void SSR::Scene::set_orientation_relative_of_selected_source(const float value)
{
  current_selected_source->set_relative_orientation(value);
}

SSR::Parameter<float, float> SSR::Scene::get_orientation_of_selected_source() const
{
  return current_selected_source->get_orientation();
}

void SSR::Scene::set_mute_absolute_of_selected_source(const bool value)
{
  current_selected_source->set_absolute_mute(value);
}

void SSR::Scene::set_mute_relative_of_selected_source(const float value)
{
  current_selected_source->set_relative_mute(value);
}

SSR::Parameter<bool, float> SSR::Scene::get_mute_of_selected_source() const
{
  return current_selected_source->get_mute();
}

void SSR::Scene::set_model_point_absolute_of_selected_source(const bool value)
{
  current_selected_source->set_absolute_model_point(value);
}

void SSR::Scene::set_model_point_relative_of_selected_source(const float value)
{
  current_selected_source->set_relative_model_point(value);
}

SSR::Parameter<bool, float> SSR::Scene::get_model_point_of_selected_source() const
{
  return current_selected_source->get_model_point();
}

void SSR::Scene::set_fixed_absolute_of_selected_source(const bool value)
{
  current_selected_source->set_absolute_fixed(value);
}

void SSR::Scene::set_fixed_relative_of_selected_source(const float value)
{
  current_selected_source->set_relative_fixed(value);
}

SSR::Parameter<bool, float> SSR::Scene::get_fixed_of_selected_source() const
{
  return current_selected_source->get_fixed();
}

void SSR::Scene::set_name_of_selected_source(const std::string value)
{
  set_name_of_source(current_selected_source->get_id(), value);
}

std::string SSR::Scene::get_name_of_selected_source() const
{
  return current_selected_source->get_name();
}

void SSR::Scene::set_properties_file_of_selected_source(const std::string value)
{
  current_selected_source->set_properties_file(value);
}

std::string SSR::Scene::get_properties_file_of_selected_source() const
{
  return current_selected_source->get_properties_file();
}

void SSR::Scene::set_jackport_of_selected_source(const std::string value)
{
  current_selected_source->set_jackport(value);
}

std::string SSR::Scene::get_jackport_of_selected_source() const
{
  return current_selected_source->get_jackport();
}

// PRIVATE

bool SSR::Scene::id_already_in_use(unsigned int id_to_check)
{
  return std::any_of(begin(*ids_and_names), end(*ids_and_names), [&id_to_check](std::pair<unsigned int, std::string> p){ return id_to_check == p.first; });
}

unsigned int SSR::Scene::get_next_id()
{
  unsigned int next_id = 1;
  std::for_each(begin(*ids_and_names), end(*ids_and_names), [&next_id](std::pair<unsigned int, std::string> p){

    if (next_id == p.first) {
        next_id++;
    }

  });
  return next_id;
}

const source_iterator SSR::Scene::get_iterator(unsigned int id)
{

  if (id_already_in_use(id)) {
    return std::find_if(begin(*sources), end(*sources), [id](const SSR::Source s) { return id == s.get_id(); }  );
  } else {
    throw std::runtime_error("Source does not exist!");
  }

}

void SSR::Scene::manipulate_source(source_iterator source_to_manipulate, juce::XmlElement* element)
{


  if (element->hasAttribute("volume")) {
      source_to_manipulate->set_absolute_gain(static_cast<float>(element->getDoubleAttribute("volume")), false);
  }

  if (element->hasAttribute("name")) {
      std::string name = element->getStringAttribute("name").toStdString();
      set_name_of_source(source_to_manipulate->get_id(), name);
  }

  if (element->hasAttribute("mute")) {
      source_to_manipulate->set_absolute_mute(element->getBoolAttribute("mute"));
  }

  if (element->hasAttribute("model")) {
      source_to_manipulate->set_absolute_model_point(element->getStringAttribute("model").toStdString() == "point");
  }

  if (element->hasAttribute("properties_file")) {
      source_to_manipulate->set_properties_file(element->getStringAttribute("properties_file").toStdString());
  }

  forEachXmlChildElement(*element, f) {

    if (f->hasTagName("position")) {

        if (f->hasAttribute("x")) {
            source_to_manipulate->set_x_position_absolute(static_cast<float>(f->getDoubleAttribute("x")));
        }

        if (f->hasAttribute("y")) {
            source_to_manipulate->set_y_position_absolute(static_cast<float>(f->getDoubleAttribute("y")));
        }

        if (f->hasAttribute("fixed")) {
            source_to_manipulate->set_absolute_fixed(f->getBoolAttribute("fixed"));
        } else {
            source_to_manipulate->set_absolute_fixed(false);
        }

    } else {

        if (f->hasTagName("orientation")) {

            if (f->hasAttribute("azimuth")) {
                source_to_manipulate->set_absolute_orientation(static_cast<float>(f->getDoubleAttribute("azimuth")));
            }

        } else {

            if (f->hasTagName("port")) {
                //WARNING: I put the getAllSubText() method in here because with getText()
                //I dont get the string of the port
                source_to_manipulate->set_jackport(f->getAllSubText().toStdString());
            }

        }

    }

  }

}

void SSR::Scene::set_name_of_source(const unsigned int id, const std::string name)
{
  auto source = get_iterator(id);
  source->set_name(name);
  std::for_each(begin(*ids_and_names), end(*ids_and_names), [&id, &name](std::pair<unsigned int, std::string> p) {

    if (p.first == id) {
        p.second = name;
    }

  });

}

void SSR::Scene::set_id_of_source(const unsigned int id, const unsigned int new_id)
{
  auto source = get_iterator(id);
  source->set_id(new_id);
  std::for_each(begin(*ids_and_names), end(*ids_and_names), [&id, &new_id](std::pair<unsigned int, std::string> p) {

    if (p.first == id) {
        p.first = new_id;
    }

  });
}
