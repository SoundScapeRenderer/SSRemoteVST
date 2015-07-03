#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

//C++ Libs
#include <string>
#include <sstream>
#include <array>
#include <memory>

//JUCE Libs
#include <JuceHeader.h>

//Own Libs
#include <src/utils/iconnection.h>

namespace SSR {

/**
* This class represents a tcp client connection and is basically a wrapper class
* of the JUCE class StreamingSocket.
*
* This class provides methods to connect to a host and disconnect from it,
* methods to get messages from the host and send messages to the host and a 
* method to check whether this client is connected to the host.  
*
* Warning: This class should implement an interface allready written but this
* does not work properly, so this is something to work on...
*
* @author 	Florian Willich
* @version 	0.7
* @date 	2014-11-14
**/
class TCP_connection : public SSR::IConnection
{

public:

	/**
	* This constructor needs a hostname, a port and a timeout for the  connect()
	* method and the end_of_message char for incoming messages.
	*
	* @param 		hostname 			The hostname (domain name or ip address)
	*									to connect to.
	*
	* @param 		prot 				The port on which to send and receive 
	*									messages.
	*
	* @param 		timeout 			Timeout in milliseconds when trying to 
	* 									connect to the host.
	*
	* @param 		end_of_message 		The char that represents the end of a 
	* 									message when receiving a message from 
	* 									the host.
	*
	* @author 		Florian Willich
	**/
	TCP_connection(const std::string hostname, const int port, const int timeout, const char end_of_message);

	/**
	* Deconstructor which also disconnects if not allready done.
	**/
	virtual ~TCP_connection();

	/**
	* This method connects this client to the given host with the parameters 
	* transfered by creating this object. 
	* 
	* @return 		true if the connection was succesfull, false otherwise.
	* @author 		Florian Willich
	**/
	virtual bool connect();

	/**
	* This method disconnects this client from the given host with the 
	* parameters transfered by creating this object.
	*
	* @author 		Florian Willich
	**/
	virtual void disconnect();

	/**
	* This method gets a message from the host which ends with the transfered 
	* parameter end_of_message by creating this object.
	*
	* @param 	new_message 		The message received from the host will be 
	* 								put into this string without the character
	* 								representing the end of the message.
	*
	* @param 	wait_in_msec 		The time in milliseconds waiting for a
	*								message to come in.
	*
	* @return 						true if there is a new message, otherwise
	*								false.
	*
	* @author 		Florian Willich
	**/
	virtual bool get_message(std::shared_ptr<std::string> new_message, int* wait_in_msec);

	/**
	* This method sends the transfered message_to_send to the host.
	*
	* @param 	message_to_send 	The message that will be send to the host.
	* @param 	wait_in_msec 		The time in milliseconds waiting for the
	* 								being ready to receive a message.
	* @return 						true if sending the message was successful,
	*								false otherwise.
	*
	* @author 		Florian Willich
	**/
	virtual bool send_message(const std::shared_ptr<std::string> message_to_send, int wait_in_msec);

	/**
	* This method returns a boolean value if the client is connected to the
	* host. 
	* 
	* WARNING: It does not check whether the host is unreachable after
	* the initial connection was successfully established.
	*
	* @return 						true if the client is connected to the host,
	* 								otherwise false. Please pay attention to the
	*								warning mentioned above.
	*
	* @author 		Florian Willich
	**/
	virtual bool is_connected() const;

private:

	/**
	* This method reads the incoming message.
	* 
	* @param 	wait_in_msec 		The time in milliseconds waiting for a
	*								message to come in.
	*
	* @author 		Florian Willich
	**/
	void read_message(int* wait_in_msec);

	/**
	* This methods loads the incoming_message_buffer with new messages coming
	* from the host.
	*
	* @param 	wait_in_msec 		The time in milliseconds waiting for a
	*								message to come in.
	*
	* @author 		Florian Willich
	**/
	bool load_buffer(int* wait_in_msec);

private:

	/**
	* The hostname which can be a domain name or IP adress.
	**/
	std::string hostname;

	/**
	* The port on which the service runs on.
	**/
	int port;

	/**
	* The timeout in milliseconds waiting for the host by connecting to it.
	**/
	int timeout;

	/**
	* The character representing the end of a message of incoming messages.
	**/
	char end_of_message;

	/**
	* Stringstream for incoming messages handling.
	**/
	std::stringstream* ss;

	/**
	* JUCE StreamingSocket object which does all the basic socket work.
	**/
	StreamingSocket ss_connection;

	/**
	* Represents if there is a new message available from the host or not.
	**/
	bool new_message_available;

	/**
	* Index for the incoming_message_buffer which is needed to work with 
	* it more efficient.
	**/
	int buffer_index;

	/**
    * The buffer which is used for the incoming messages limited to 128 chars.
    **/
    std::array<char, 128> incoming_message_buffer;
	
};

}

#endif
