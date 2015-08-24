#ifndef SSR_REQUESTER_H
#define SSR_REQUESTER_H

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
#include <sstream>
#include <functional>

namespace SSR 
{

  /**
   * With this class you can build XML requests for the SSR.
   * The class provides a build method which does all the work. Please read the
   * documentation of `build` for more detailed information how to build XML
   * requests.
   *
   * For more detailed information for SSR requests, please visit:
   * http://ssr.readthedocs.org
   *
   * @see build
   **/
  class SSR_requester
  {

  public:

    /**
     * The constructor for the SSR requester.
     **/
    SSR_requester();

    /**
     * The deconstructor for the SSR requester.
     **/
    ~SSR_requester();

    /**
     * Defines the signature of the build function needed by the method build.
     *
     * @see      build           The method which calls this function type.
     **/
    typedef std::function<void(std::ostream* output)> Build_function;

    /**
     * With this Method you can build various SSR requests.
     *
     * Use:
     * build(std::bind(SSR::request::<function>, std::placeholders::_1, <value1>, ..., <valueN>))
     *
     * The transfered function has to have a pointer to an ostream thats why
     * there is the need for the placeholder.
     * The method returns the build SSR request always beginning with <request>
     * and ends with </request>:
     *
     * `<request>INPUT</request>`
     *
     * @param        fun         A function which has to have an ostream as
     *                           argument.
     *
     * @return       the build SSR request.
     **/
    const std::string build(Build_function bf);

  private:

    /**
     * The request string stream with which all requests are concatenated.
     **/
    std::stringstream* request_ss;

  };

  namespace request
  {

    /**
     * This function writes the source position XML request statement into output
     * as follows:
     *
     * `<source id="source_id"><position x="x" y="y"/></source>`
     *
     * For more detailed information please visit: http://ssr.readthedocs.org
     *
     * @param        output          The stream in which the XML request is
     *                               written.
     * @param        source_id       The source ID.
     * @param        x               The position on the X axis.
     * @param        y               The position on the Y axis.
     **/
    void source_position(std::ostream* output, const float source_id, const float x, const float y);

    /**
     * This function writes the source gain XML request statement into output
     * as follows:
     *
     * `<source id="source_id" volume="gain_in_db"/>`
     *
     * For more detailed information please visit: http://ssr.readthedocs.org
     *
     * @param        output              The stream in which the XML request is
     *                                   written.
     * @param        source_id           The source ID.
     * @param        gain_in_db          The gain in dB which shall be assigned
     *                                   to the source.
     **/
    void source_gain(std::ostream* output, const float source_id, const float gain_in_db);

    /**
     * This function writes the source mute XML request statement into output
     * as follows:
     *
     * `<source id="source_id" mute="mute"/>`
     *
     * For more detailed information please visit: http://ssr.readthedocs.org
     *
     * @param       output           The stream in which the XML request is
     *                               written.
     * @param       source_id        The source ID.
     * @param       mute             True if the source shall be muted.
     **/
    void source_mute(std::ostream* output, const int source_id, const bool mute);

    /**
     * This function writes the source fixed XML request statement into output
     * as follows:
     *
     * `<source id="source_id"><position fixed="fixed"/></source>`
     *
     * For more detailed information please visit: http://ssr.readthedocs.org
     *
     * @param       output           The stream in which the XML request is
     *                               written.
     * @param       source_id        The source ID.
     * @param       fixed            True if the source shall be fixed
     **/
    void source_fixed(std::ostream* output, const int source_id, const bool fixed);

    /**
     * This function writes the source model XML request statement into output
     * as follows:
     *
     * `<source id="source_id" model="model"/>`
     *
     * Possible models are: `"point"` or `"plane"`.
     * For more detailed information please visit: http://ssr.readthedocs.org
     *
     * @param       output           The stream in which the XML request is
     *                               written.
     * @param       source_id        The source ID.
     * @param       model            The model type of the source ("point" or
     *                               "plane") which shall be assigned.
     **/
    void source_model(std::ostream* output, const int source_id, const std::string model);

    /**
     * This function writes the source name XML request statement into output
     * as follows:
     *
     * `<source id="source_id" name="name"/>`
     *
     * For more detailed information please visit: http://ssr.readthedocs.org
     *
     * @param       output           The stream in which the XML request is
     *                               written.
     * @param       source_id        The source ID.
     * @param       name             The name which shall be assigned to the
     *                               source
     **/
    void source_name(std::ostream* output, const int source_id, const std::string name);

    /**
     * This function writes the properties file XML request statement into output
     * as follows:
     *
     * `<source id="source_id" properties_file="properties_file"/>`
     *
     * For more detailed information please visit: http://ssr.readthedocs.org
     *
     * @param       output           The stream in which the XML request is
     *                               written.
     * @param       source_id        The source ID.
     * @param       properties_file  The name of the properties file which the
     *                               source shall use.
     **/
    void source_properties_file(std::ostream* output, const int source_id, const std::string properties_file);

    /**
     * This function writes the port XML request statement into output
     * as follows:
     *
     * `<source id="source_id" port="port"/></source>`
     *
     * For more detailed information please visit: http://ssr.readthedocs.org
     *
     * WARNING: Since this is only possible at the creation of the source, this
     *          works only one time at the moment (Bug #1778)
     *
     * @param       output           The stream in which the XML request is
     *                               written.
     * @param       source_id        The source ID.
     * @param       port             The port with which the source shall be
     *                               connected with (Jackport).
     **/
    void source_port(std::ostream* output, const int source_id, const std::string port) ;

    /**
     * This function writes the new source XML request statement into output as
     * follows:
     *
     * `<source new="true" name="<name>" port="<port>"><position x="<x_position>" y="y_position"></source>"`
     *
     * @param           output          The stream in which the XML request is
     *                                  written.
     * @param           name            The new name of the source.
     * @param           port            The Jackport on with which the source shall connect to.
     * @param           x_position      The initial position on the x axis of the new source.
     * @param           y_position      The initial position on the y axis of the new source.
     */
    void new_source(std::ostream* output, const std::string name, const std::string port, const float x_position, const float y_position);

  }

}


#endif
