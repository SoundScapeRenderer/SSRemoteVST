#ifndef CONTROLLER_H
#define CONTROLLER_H

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

#include <algorithm> 
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

//Own classes
#include <src/utils/jack_client.h>
#include <src/utils/tcp_connection.h>
#include <src/utils/ssr_requester.h>
#include <src/parameter/parameter.h>
#include <src/config/config.h>
#include <src/utils/update_specificator.h>
#include <src/scene/scene.h>

//Boost
#include <boost/filesystem.hpp>

#define LOG_TO_FILE 1

//==============================================================================
/**
 */
class Controller 
		: public AudioProcessor
{
public:
	//==============================================================================
	Controller();
	virtual ~Controller();

	//==============================================================================
	void prepareToPlay (double sampleRate, int samplesPerBlock);
	void releaseResources();

	void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

	//==============================================================================
	AudioProcessorEditor* createEditor();
	bool hasEditor() const;

	//==============================================================================
	const String getName() const;

	virtual int getNumParameters() override;



	/**
    void set_parameter_source_orientation(const float value);
	 **/

	/**
	 * Return the parameter value.
	 **/
	virtual float getParameter(int index) override;

	virtual void setParameter(int parameterIndex, float newValue) override;

	/**
	 * Return the parameter as a JUCE String.
	 **/
	virtual const String getParameterText(int index) override;

	/**
	 * Return the parameter name as a JUCE String.
	 **/
	virtual const String getParameterName (int parameterIndex) override;

	/**
	 * Return the input channel name as a JUCE String.
	 **/
	virtual const String getInputChannelName (int channelIndex) const override;

	/**
	 * Returns the output channel name as a JUCE String.
	 **/
	virtual const String getOutputChannelName (int channelIndex) const override;

	bool isInputChannelStereoPair (int index) const;
	bool isOutputChannelStereoPair (int index) const;

	bool acceptsMidi() const;
	bool producesMidi() const;
	bool silenceInProducesSilenceOut() const;
	double getTailLengthSeconds() const;

	//==============================================================================

	/**
	 * Returns the number of preset programs the filter supports.
	 * The value returned must be valid as soon as this object is created, and must
	 * not change over its lifetime. This value shouldn't be less than 1.
	 *
	 * @return the number of preset programs the filter supports.
	 *
	 * @see http://www.juce.com/api/classAudioProcessor.html#a510123768a99f32ff4a23d0458e15e13
	 */
	virtual int getNumPrograms() override;


	/**
	 * Returns the number of the currently active program.
	 *
	 * @return the number of the currently active program.
	 *
	 * @see http://www.juce.com/api/classAudioProcessor.html
	 */
	virtual int getCurrentProgram() override;

	/**
	 * JUCE Doc: Called by the host to change the current program.
	 *
	 * Since we do no provide any program, the set does not set anything...
	 *
	 * @see http://www.juce.com/api/classAudioProcessor.html
	 */
	virtual void setCurrentProgram(int index) override;

	/**
	 * JUCE Doc: Must return the name of a given program.
	 *
	 * Since there is no name of any program, we just return "SSR Scene Automation".
	 *
	 * @param 	index 	The index of the program which name shall be returned.
	 *
	 * @return the name of the given program.
	 *
	 * @see http://www.juce.com/api/classAudioProcessor.html
	 */
	virtual const juce::String getProgramName(int index) override;

	/**
	 * JUCE Doc: Called by the host to rename a program.
	 *
	 * @param
	 */
	virtual void changeProgramName (int index, const String& newName) override;

	//==============================================================================
	void getStateInformation (MemoryBlock& destData);
	void setStateInformation (const void* data, int sizeInBytes);


	//==============================================================================
	// PUT YOUR OWN PUBLIC STUFF HERE!
	//==============================================================================

	SSR::Source get_source() const;
	void set_parameter_source_x_position(const float value);
	void set_parameter_source_y_position(const float value);
	void set_parameter_source_gain(const float value, const bool linear);
	void set_parameter_source_mute(const bool value);
	void set_parameter_source_model_point(const bool value);
	void set_parameter_source_fixed(const bool value);
	void set_parameter_source_name(const std::string value);
	void set_parameter_source_properties_file(const std::string value);
	void set_parameter_source_port(const std::string value);
	bool reset_source(const int source_id);

	void new_source();

	/**
	 * This method reads the incoming message from the SSR server, interprets
	 * them and updates the members if there have been any request of doing so
	 * from the SSR server.
	 *
	 * @return       if there was any message from the SSR server to interpret.
	 **/
	bool read_ssr_incoming_message();

	void connect();

	/**
	 * Returns true if the connection to SSR is established.
	 **/
	bool is_connected_to_ssr() const;

	/**
	 * Returns true if the UI needs update.
	 **/
	bool ui_needs_update() const;

	/**
	 * Sets the ui_update_flag on true for requesting update.
	 **/
	void ui_request_update();

	/**
	 * Clears the ui_update_flag by setting it on false.
	 **/
	void ui_clear_update_flag();

	/**
	 * This method returns all Jack Ports specified by the flags.
	 *
	 * @param    flags       Flags to specify which Jack Ports shall be returned.
	 *
	 * @return   all jackports specified by the flags.
	 **/
	std::vector<std::string> get_all_jack_ports(const unsigned long flags);

	void update_ssr(SSR::Update_specificator specificator);

	std::shared_ptr< std::vector< std::pair<unsigned int, std::string> > > get_source_ids_and_names();

private:

	//==============================================================================
	// PRIVATE METHODS

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controller)

	/**
	 * If message_from_ssr_complete = true, the message will be send to the ssr.
	 **/
        void send_message_to_ssr();

	/**
	 * Returns a the valid config file path (including the file name).
	 * The file path is concatenated as follows:
	 *
	 * 1.   The config file path is loaded by the currently set environment variable
	 *      $SSREMOTE_CONFIG
	 * 2.   The name of the config file: ssremote_config.xml
	 *
	 * Those two components are concatenated to one file path which should be valid.
	 * If the path is not valid, there will be a console output to std::cerr.
	 *
	 * TODO: Should there be any mechanic to create the file if it does not exist?
	 *
	 * @return a the valid config file path (including the file name).
	 *
	 * @author Florian Willich
	 */
	boost::filesystem::path get_config_file_path();

	std::map<int, std::string> extract_source_names(std::string& message);

private:

	/**
	 * Bool flag indicating if the user interface needs to be updated (= true).
	 **/
	bool ui_update_flag;

	/**
	 * TCP connection object for connecting to ssr.
	 **/
	std::unique_ptr<SSR::IConnection> tcp_connection;

	/**
	 * The message that will be send to the SSR server.
	 * It has to include the '\0' also called EOF ending so the SSR server understands
	 * that this is the end of the message.
	 **/
	std::shared_ptr<std::string> message_to_ssr;

	/**
	 * The message that comes from the SSR server.
	 * It has to have an '\0' at the end.
	 **/
	std::shared_ptr<std::string> message_from_ssr;

	/**
	 * The jack client managing the provided jack ports.
	 */
	std::unique_ptr<SSR::Jack_client> jack_client;

	/**
	 * This is the SSR requester, requesting changes of the SSR scene.
	 *
	 * This requester will not share any resources with other objects and
	 * thus is a unique_ptr.
	 */
	std::unique_ptr<SSR::SSR_requester> requester;


	std::unique_ptr<SSR::Config> config;

	std::unique_ptr< SSR::Scene > scene;

	//==============================================================================

};


#endif
