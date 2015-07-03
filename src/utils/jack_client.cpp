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

#include <memory>

#include <src/utils/jack_client.h>

SSR::Jack_client::Jack_client()
	: client(nullptr)
{   
    status = JackFailure;
}

SSR::Jack_client::~Jack_client()
{

	if (status & JackServerStarted) {
		jack_client_close(client);
	}

}

void SSR::Jack_client::register_client(const char* jack_client_name)
{
	client = jack_client_open(jack_client_name, JackNoStartServer, &status);

	if (status & JackServerFailed) {
		throw jack_server_not_running_exception();
	}

}

std::vector<std::string> SSR::Jack_client::look_up_jack_ports(unsigned long flags)
{
	if (status & JackFailure) {
		throw jack_server_not_running_exception();
	}

	const char **ports;

	if (NULL == (ports = jack_get_ports(client, NULL, NULL, flags))) {  
		throw no_jack_ports_available_exception();
	}

	std::vector<std::string> v_ports;

    for (int i = 0; ports[i] != NULL; i++) {
    	v_ports.push_back(ports[i]);
    }

    free(ports);

    return v_ports;
}
