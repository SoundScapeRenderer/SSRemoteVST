#ifndef NETWORK_CONFIG_H
#define NETWORK_CONFIG_H

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

#include <string>

namespace SSR
{

    class Network_config
    {

    public:
        Network_config();

        Network_config(std::string hostname, unsigned int port, unsigned int timeout_in_ms, char end_of_message);

        ~Network_config();

        void set_hostname(const std::string new_hostname);

        void set_port(const unsigned int new_port);

        void set_timeout(const unsigned int new_timeout_in_ms);

        void set_end_of_message(char new_end_of_message);

        std::string get_hostname() const;

        unsigned int get_port() const;

        unsigned int get_timeout() const;

        char get_end_of_message() const;

    private:
        std::string hostname;
        unsigned int port;
        unsigned int timeout_in_ms;
        char end_of_message;

    };

}

std::ostream& operator<<(std::ostream& stream, const SSR::Network_config& network_config);

#endif
