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
    /**
    * This class represents the network config of the SSRemoteVST:
    * To successfully remote operate with the SSR the SSRemoteVST needs to
    * know the following information:
    *
    * - the hostname of the machine where the SSR is executed on
    * - the port on which the SSR TCP/IP socket listens on
    *
    * Additionally, the following information is needed:
    *
    * - the timeout in milliseconds to determine when the SSR is unreachable
    *   for network operations
    * - the character that determines the end of a message that is incoming
    *   from and outgoing to the SSR
    *
    * @since 2015-08-03
    * @author Florian Willich
    */
    class Network_config
    {

    public:

        /**
        * Standard constructor which sets the members as follwos:
        *
        * - hostname: "localhost"
        * - port: 4711
        * - timeout_in_ms: 1000
        * - end_of_message: '\0'
        *
        * @author Florian Willich
        */
        Network_config();

        /**
        * Constructor setting all members to the transferred parameters.
        *
        * @param       hostname        The hostname of the machine where the
        *                              SSR is executed on.
        *
        * @param       port            The port on wich the SSR TCP/IP socket
        *                              listens on.
        *
        * @param       timeout_in_ms   The timeout in milliseconds to
        *                              determine when the SSR is unreachable
        *                              for network operations.
        *
        * @param       end_of_message  The character that determines the end
        *                              of a message that is incoming from and
        *                              outgoing to the SSR.
        *
        * @author Florian Willich
        */
        Network_config(std::string hostname, unsigned int port, unsigned int timeout_in_ms, char end_of_message);

        /**
        * Destructor.
        */
        ~Network_config();

        /**
        * Setter for the hostname of the machine where the SSR is executed on.
        *
        * @param       new_hostname    The hostname of the machine where the
        *                              SSR is executed on.
        *
        * @author Florian Willich
        */
        void set_hostname(const std::string new_hostname);

        /**
        * Setter for the port on wich the SSR TCP/IP socket listens on.
        *
        * @param       new_port        The port on wich the SSR TCP/IP socket
        *                              listens on.
        *
        * @author Florian Willich
        */
        void set_port(const unsigned int new_port);

        /**
        * Setter for the timeout in milliseconds to determine when the SSR is
        * unreachable for network operations.
        *
        * @param       new_timeout_in_ms       The timeout in milliseconds to
        *                                      determine when the SSR is
        *                                      unreachable for network
        *                                      operations.
        *
        * @author Florian Willich
        */
        void set_timeout(const unsigned int new_timeout_in_ms);

        /**
        * Setter for the character that determines the end of a message that
        * is incoming from and outgoing to the SSR.
        *
        * @param       new_end_of_message      The character that determines
        *                                      the end of a message that is
        *                                      incoming from and outgoing to
        *                                      the SSR.
        *
        * @author Florian Willich
        */
        void set_end_of_message(char new_end_of_message);

        /**
        * Returns the hostname of the machine where the SSR is executed on.
        *
        * @return the hostname of the machine where the SSR is executed on.
        *
        * @author Florian Willich
        */
        std::string get_hostname() const;

        /**
        * Returns the port on wich the SSR TCP/IP socket listens on.
        *
        * @return the port on wich the SSR TCP/IP socket listens on.
        *
        * @author Florian Willich
        */
        unsigned int get_port() const;

        /**
        * Returns the timeout in milliseconds to determine when the SSR is
        * unreachable for network operations.
        *
        * @return the timeout in milliseconds to determine when the SSR is
        * unreachable for network operations.
        *
        * @author Florian Willich
        */
        unsigned int get_timeout() const;

        /**
        * Returns the character that determines the end of a message that
        * is incoming from and outgoing to the SSR.
        *
        * @return the character that determines the end of a message that
        * is incoming from and outgoing to the SSR.
        *
        * @author Florian Willich
        */
        char get_end_of_message() const;

    private:
        
        /**
        * The hostname of the machine where the SSR is executed on.
        */
        std::string hostname;
        
        /**
        * The port on wich the SSR TCP/IP socket listens on.
        */
        unsigned int port;
        
        /**
        * The timeout in milliseconds to determine when the SSR is unreachable
        * for network operations.
        */
        unsigned int timeout_in_ms;
        
        /**
        * The character that determines the end of a message that is incoming
        * from and outgoing to the SSR.
        */
        char end_of_message;

    };

}

/**
* Shift left operator for printing out a network configuration object when an
* ostream is on the left side.
*
* @param       stream          The output stream where the string
*                              representation of the network configuration
*                              object is streamed to.
*
* @param       network_config  The network configuration which shall be
*                              represented.
*
* @return      the stream including the string representation of the network
*              configuration.
*
* @author Florian Willich
*/
std::ostream& operator<<(std::ostream& stream, const SSR::Network_config& network_config);

#endif
