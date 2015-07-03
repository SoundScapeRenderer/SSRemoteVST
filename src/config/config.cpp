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

#include <ostream>
#include <sstream>
#include <string>

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>

#include <src/config/config.h>

SSR::Config::Config(boost::filesystem::path& config_file)
: config_file(config_file)
, network_config(new SSR::Network_config())
{

}

SSR::Config::~Config()
{
    write_config_xml_file();
}

void SSR::Config::load_config_xml_file()
{
    boost::property_tree::ptree document;

    try {
        boost::property_tree::read_xml(config_file.generic_string(), document);

        //Get all config stuff
        std::string hostname    = document.get("config.network.host", "localhost");
        int port                = document.get("config.network.port", 4711);
        int timeout             = document.get("config.network.tiemout", 1000);

        set_network_config(hostname, port, timeout);

    } catch (const boost::property_tree::xml_parser::xml_parser_error& e) {
        std::cerr << "Exception Thrown in Config::load_config_xml_file() Method!" << std::endl;
        std::cerr << e.what() << std::endl;
    }

}

void SSR::Config::write_config_xml_file()
{
    boost::property_tree::ptree document;

    document.put("config.network.host", network_config->get_hostname());
    document.put("config.network.port", network_config->get_port());
    document.put("config.network.timeout", network_config->get_timeout());

    try {
        boost::property_tree::write_xml(config_file.generic_string(), document);
    } catch (const boost::property_tree::xml_parser::xml_parser_error& e) {
        std::cerr << "Exception Thrown in Config::load_config_xml_file() Method!" << std::endl;
        std::cerr << e.what() << std::endl;
    }

}

SSR::Network_config SSR::Config::get_network_config() const
{
    return *network_config;
}

boost::filesystem::path SSR::Config::get_config_file_path() const
{
  return config_file;
}

void SSR::Config::set_hostname(const std::string new_hostname)
{
    network_config->set_hostname(new_hostname);
}

void SSR::Config::set_port(const unsigned int new_port)
{
    network_config->set_port(new_port);
}

void SSR::Config::set_timeout(const unsigned int new_timeout_in_ms)
{
    network_config->set_timeout(new_timeout_in_ms);
}

void SSR::Config::set_end_of_message(char new_end_of_message)
{
    network_config->set_end_of_message(new_end_of_message);
}

void SSR::Config::set_network_config(std::string hostname, unsigned int port, unsigned int timeout)
{
    network_config->set_hostname(hostname);
    network_config->set_port(port);
    network_config->set_timeout(timeout);
}

std::ostream& operator<<(std::ostream& stream, const SSR::Config& config)
{
    std::stringstream ss;
    ss << "[Config]" << std::endl;
    ss << "Config Filename: " << config.get_config_file_path().filename() << std::endl << std::endl;
    ss << config.get_network_config();
    return stream << ss.str();
}
