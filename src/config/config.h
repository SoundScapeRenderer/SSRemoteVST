#ifndef CONFIG_H
#define CONFIG_H

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
#include <memory>

//Boost Libs
#include <boost/filesystem.hpp>

//Own Libs
#include <src/config/network_config.h>


namespace SSR
{

    /**
     * This class represents the user specific configuration for the
     * SSRemoteVST such as the network configuration.
     *
     * This class provides methods for loading a xml config file and writing a
     * xml config file. It also provides an interface to configure the network
     * configuration.
     *
     * @see network_config.h
     * @author Florian Willich
     * @since 2015-06-30
     */
    class Config
    {

    public:

        /**
         * Constructor taking the config_file parameter which shall point to
         * the config file location.
         *
         * @param       config_file_location    The directory and filename
         *                                      where the config file is
         *                                      located.
         *
         * @author Florian Willich
         */
        Config(boost::filesystem::path& config_file);

        /**
         * Destructor which writes the config to (XML) file.
         */
        ~Config();

        /**
         * Reads the config XML file and sets all related members to the
         * configs settings.
         *
         * @author Florian Willich
         */
        void load_config_xml_file();

        /**
         * Writes the config XML file with all settings that have been made.
         *
         * @author Florian Willich
         */
        void write_config_xml_file();

        /**
         * Getter for the network configuration.
         *
         * @return the network configuration.
         *
         * @author Florian Willich
         */
        SSR::Network_config get_network_config() const;

        /**
         * Getter for the config file path.
         *
         * @return the config file path.
         *
         * @author Florian Willich
         */
        boost::filesystem::path get_config_file_path() const;

        /**
         * Setter for the hostname.
         *
         * @param       new_hostname    The new hostname.
         *
         * @author Florian Willich
         */
        void set_hostname(const std::string new_hostname);

        /**
         * Setter for the port.
         *
         * @param       new_port        The new port.
         *
         * @author Florian Willich
         */
        void set_port(const unsigned int new_port);

        /**
         * Setter for the timeout.
         *
         * @param       new_timeout_in_ms       The new timout in milliseconds.
         *
         * @author Florian Willich
         */
        void set_timeout(const unsigned int new_timeout_in_ms);

        /**
         * Setter for the character that defines the end of a message.
         *
         * @param       new_end_of_message      The new character that defines
         *                                      the end of a message.
         *
         * @author Florian Willich
         */
        void set_end_of_message(char new_end_of_message);

    private:

        /**
         * Method that sets the network config with the transfered parameters.
         *
         * @param       hostname        The new hostname.
         * @param       port            The new port.
         * @param       timeout         The new timout.
         *
         * @author      Florian Willich
         */
        void set_network_config(std::string hostname, unsigned int port, unsigned int timeout);

    private:

        /**
         * The network configuration.
         */
        std::unique_ptr<SSR::Network_config> network_config;

        /**
         * The config file location including the direcotry and filename.
         */
        boost::filesystem::path config_file;

    };

}

/**
 * Shift left operator for printing out a SSR Config object when an ostream
 * is on the left side.
 *
 * @param       stream          The output stream where the string
 *                              representation of the SSR Config object is
 *                              streamed to.
 * @param       config          The SSR Config object which will be represented
 *                              as a string.
 *
 * @return      the stream including the string representation of the network
 *              configuration.
 *
 * @author Florian Willich
 */
std::ostream& operator<<(std::ostream& stream, const SSR::Config& config);

#endif
