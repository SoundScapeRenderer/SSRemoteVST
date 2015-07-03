#ifndef ICONNECTION_H
#define ICONNECTION_H

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

namespace SSR 
{

/**
* This interface class represents a network connection.
*
* @author Florian Willich
* @version 0.8
**/
class IConnection
{

public:

	/**
	* Destructor.
	**/
	inline virtual ~IConnection() { };

	/**
	* This method shall connect to a server.
	*
	* @return 	true if connection was successfully, otherwise false.
	**/
	virtual bool connect() = 0;

	/**
	* This method shall disconnect from the server.
	**/
	virtual void disconnect() = 0;

	/**
	* This method shall get a new message coming from the connected server.
	*
	* @param 		new_message 		The new message from the connected
	* 									server.
	* 
	* @param 		wait_in_msec 		How many milliseconds this method shall
	*									wait to receive a new message from the
	* 									server.
	*
	* @return 		true if a new message was received, otherwise false.
	**/
	virtual bool get_message(std::shared_ptr<std::string> new_message, int* wait_in_msec) = 0;

	/**
	* This method shall send a message to the connected server.
	*
	* @param 		message_to_send 	The message that shall be send to the
	* 									server.
	*
	* @param 		wait_in_msec 		How many milliseconds this method shall
	*									wait until the server is read to reveive
	*									a new message from this client server.
	* 
	* @return 		true if the message was send to the server, otherwise false.
	**/
	virtual bool send_message(const std::shared_ptr<std::string> message_to_send, int wait_in_msec) = 0;

	/**
	* This method shall return if this client is connected to the server.
	* WARNING: This method does not test wether the connection is interrupted
	* it only checks wether this client had already established a connection
	* to the server.
	*
	* @return		true if the client is connected to the server, otherweise 
	* 				false. 
	**/	
	virtual bool is_connected() const = 0;	
	
};

}


#endif
