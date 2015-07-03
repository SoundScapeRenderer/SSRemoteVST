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

#include <src/config/network_config.h>

//C++ Libs
#include <ostream>
#include <sstream>

SSR::Network_config::Network_config()
        : hostname("localhost")
        , port(4711)
        , timeout_in_ms(1000)
        , end_of_message('\0')
{

}

SSR::Network_config::Network_config(std::string hostname, unsigned int port, unsigned int timeout_in_ms, char end_of_message)
: hostname(hostname)
, port(port)
, timeout_in_ms(timeout_in_ms)
, end_of_message(end_of_message)
{

}

SSR::Network_config::~Network_config()
{

}

void SSR::Network_config::set_hostname(const std::string new_hostname)
{
    hostname = new_hostname;
}

void SSR::Network_config::set_port(const unsigned int new_port)
{
    port = new_port;
}

void SSR::Network_config::set_timeout(const unsigned int new_timeout_in_ms)
{
    timeout_in_ms = new_timeout_in_ms;
}

void SSR::Network_config::set_end_of_message(char new_end_of_message)
{
    end_of_message = new_end_of_message;
}

std::string SSR::Network_config::get_hostname() const
{
    return hostname;
}

unsigned int SSR::Network_config::get_port() const
{
    return port;
}

unsigned int SSR::Network_config::get_timeout() const
{
    return timeout_in_ms;
}

char SSR::Network_config::get_end_of_message() const
{
    return end_of_message;
}

std::ostream& operator<<(std::ostream& stream, const SSR::Network_config& network_config)
{
    std::stringstream ss;
    ss << "[Network Config]" << std::endl;
    ss << "Hostname: " << network_config.get_hostname() << std::endl;
    ss << "Port: " << network_config.get_port() << std::endl;
    ss << "Timeout: " << network_config.get_timeout() << std::endl;
    ss << "End of Message: " << network_config.get_end_of_message() << std::endl;
    return stream << ss.str();
}
