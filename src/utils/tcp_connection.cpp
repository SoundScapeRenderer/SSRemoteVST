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

#include <src/utils/tcp_connection.h>

//C++ Libs
#include <string>
#include <sstream>
#include <array>
#include <functional>

//Own Libs
#include <src/utils/iconnection.h>
#include <src/controller.h>
#include <src/utils/logger.h>

//JUCE Lib
#include <JUCE/JuceHeader.h>

//============================================================================
// PUBLIC

SSR::TCP_connection::TCP_connection(const std::string hostname, const int port, const int timeout, const char end_of_message) 
: hostname(hostname)
, port(port)
, timeout(timeout)
, end_of_message(end_of_message)
, buffer_index(0)
, ss(new std::stringstream(std::string()))
, new_message_available(false)
{

  /**
   * Initially fill the incoming_message_buffer with the EOT (end of transmission)
   * character.
   **/
  std::fill(incoming_message_buffer.begin(), incoming_message_buffer.end(), 0x04);
}

SSR::TCP_connection::~TCP_connection()
{
  delete ss;

  /**
   * Dont have to check whether the streaming socket is allready closed this is
   * managed by the StreamingSocket class itself.
   **/
  ss_connection.close();
}

bool SSR::TCP_connection::connect()
{
  return ss_connection.connect(hostname, port, timeout);
}

void SSR::TCP_connection::disconnect()
{
  /**
   * Dont have to check whether the streaming socket is allready closed this is
   * managed by the StreamingSocket class itself.
   **/
  ss_connection.close();
}

bool SSR::TCP_connection::get_message(std::shared_ptr<std::string> new_message, int* wait_in_msec)
{
  read_message(wait_in_msec);

  if (new_message_available) {
      *new_message = ss->str();

#if DEBUG_TCP_IN

      SSR::Logger::get_instance()->log(SSR::Logger::Level::INFO, "[TCP IN]: " + *new_message, true);

#endif

  }

  return new_message_available;
}

bool SSR::TCP_connection::send_message(const std::shared_ptr<std::string> message_to_send, int wait_in_msec)
{
  /**
   * From the JUCE Documentation:
   * If the socket is ready on return, this returns 1. If it times-out before
   * the socket becomes ready, it returns 0. If an error occurs, it returns -1.
   **/
  int ec = ss_connection.waitUntilReady(false, wait_in_msec);

  if (ec == 1) {

#if DEBUG_TCP_OUT

      SSR::Logger::get_instance()->log(SSR::Logger::Level::INFO, "[TCP OUT]: " + *message_to_send, true);

#endif

      ss_connection.write(message_to_send->c_str(), message_to_send->length() + 1);
  }

  return (ec == 1);
}

bool SSR::TCP_connection::is_connected() const
{
  return ss_connection.isConnected();
}

//============================================================================
// PRIVATE

void SSR::TCP_connection::read_message(int* wait_in_msec)
{
  bool load_buffer_successful = true;
  new_message_available = false;
  int tmp_index = buffer_index;

  /**
   * Clear the content of the string stream as described:
   * m.str(std::string()) -> is technically more efficient,
   * because you avoid invoking the "std::string" constructor that takes
   * "const char*"
   *
   * http://stackoverflow.com/questions/20731/in-c-how-do-you-clear-a-stringstream-variable
   **/
  ss->str(std::string());

  do {

      if (tmp_index == incoming_message_buffer.size()) {
          load_buffer_successful = load_buffer(wait_in_msec);
          tmp_index = 0x00;
      }

      if (load_buffer_successful) {

          while (tmp_index < incoming_message_buffer.size() && !new_message_available) {

              if (incoming_message_buffer[tmp_index] != end_of_message && incoming_message_buffer[tmp_index] != 0x04) {
                  (*ss) << incoming_message_buffer[tmp_index];
                  tmp_index++;
              } else {

                  if (incoming_message_buffer[tmp_index] == 0x04) {
                      tmp_index = incoming_message_buffer.size();
                      new_message_available = false;
                  } else {
                      new_message_available = true;
                      tmp_index++;
                  }


              }

          }

      }

  } while (load_buffer_successful && !new_message_available);

  if (!new_message_available) {
      tmp_index = incoming_message_buffer.size();
  }

  buffer_index = tmp_index;

}

bool SSR::TCP_connection::load_buffer(int* wait_in_msec) {

  //wait until socket is ready, waits until time_out_in_msec, moer on SocketStream
  //doc from JUCE
  int ready_flag = ss_connection.waitUntilReady(true, *wait_in_msec);

  if (ready_flag == 1) {

      //Fill the array with 0x04 == end of transmission
      std::fill(incoming_message_buffer.begin(), incoming_message_buffer.end(), 0x04);

      int bytes_read = ss_connection.read(   	&incoming_message_buffer,
                                             	incoming_message_buffer.size(),
                                             	false);

  } else {

    if (ready_flag == -1) {
        SSR::Logger::get_instance()->log(SSR::Logger::Level::ERROR, "TCP/IP connection error occurred", true);
    }

  }

  return (ready_flag == 1);
}
