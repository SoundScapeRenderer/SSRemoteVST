#ifndef JACK_CLIENT_H
#define JACK_CLIENT_H

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

//Standard C Libs
#include <stdlib.h>

//Standard C++ Libs
#include <iostream>
#include <string>
#include <exception>
#include <vector>

//Jack Libs
#include <jack/jack.h>

namespace SSR 
{

//Exceptions
struct jack_server_not_running_exception : public std::exception {

	const char * what () const throw () {
		return "Could not connect to Jack Server.";
	}

};

struct no_jack_ports_available_exception : public std::exception {

	const char * what () const throw () {
		return "Could not get any Jackports.";
	}

};

/**
 * This is a client wrapper class for the jack audio server.
 *
 * @author Florian Willich
 * @version 0.5
 **/
class Jack_client
{

public:
	Jack_client();
	~Jack_client();

	/**
	 * This method registers this Jack client to the Jack Server with the
	 * transfered jack_client_name.
	 *
	 * @param    jack_client_name    The name which identifies this client on the
	 *                               Jack server.
	 **/
	void register_client(const char* jack_client_name);

	/**
	 * This method looks for all Jack Ports that match the flags parameter and
	 * returns them.
	 *
	 * @param  flags     See JackPortFlags (jack/types.h) for all flags you can
	 *                   set.
	 *
	 * @throws   no_jack_ports_available_exception     If there are no Jack Ports
	 *                                                 available matching the
	 *                                                 transfered flags.
	 *
	 * @throws   jack_server_not_running_exception     If this jack client is not
	 *                                                 connected to the Jack
	 *                                                 server.
	 *
	 * @return   all Jack Ports that matched the flags.
	 **/
	std::vector<std::string> look_up_jack_ports(unsigned long flags);

private:
	jack_client_t* client;
	jack_status_t status;

};

}


#endif
