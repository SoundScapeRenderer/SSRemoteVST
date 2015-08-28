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

//JUCE Lib
#include <JUCE/JuceHeader.h>

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

/**
 * This class represents the controller of this VST Plugin deriving from the
 * JUCE class AudioProcessor which is the base class for plugins:
 *
 * http://learn.juce.com/doc/classAudioProcessor.php
 *
 *
 *
 * @see http://learn.juce.com/doc/classAudioProcessor.php
 */
class Controller 
    : public AudioProcessor
{

public:

  /**
   * Constructor initializing the ui_update_flag with true and the scene with a
   * range of 20.0.
   *
   * Loads the config for the VST Plugin, network connects to the SSR, registers
   * this VST Plugin at the Jack Server.
   *
   * Reads the first incoming messages from the SSR.
   */
  Controller();

  /**
   * Destructor.
   */
  virtual ~Controller();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // The following methods are derived from the AudioProcessor base class
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  /**
   * JUCE Doc.:
   *
   * Returns the name of this processor.
   *
   * @return the name of this processor.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a71affad7782adb55b183d6d4d0853253
   */
  const String getName() const override;

  /**
   * Currently there is nothing put in this method.
   *
   * JUCE Doc.:
   *
   * Called before playback starts, to let the filter prepare itself.
   *
   * The sample rate is the target sample rate, and will remain constant until
   * playback stops.
   *
   * The estimatedSamplesPerBlock value is a HINT about the typical number of
   * samples that will be processed for each callback, but isn't any kind of
   * guarantee. The actual block sizes that the host uses may be different each
   * time the callback happens, and may be more or less than this value.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#ac7ebd6fb3dd06bd023159c590e3a7d2a
   */
  void prepareToPlay(double sampleRate, int estimatedSamplesPerBlock) override;

  /**
   * JUCE Doc.:
   *
   * Called after playback has stopped, to let the filter free up any resources
   * it no longer needs.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a49e88e7d6c7c40899624beb9e3508f3a
   */
  void releaseResources() override;

  /**
   * Currently there is nothing put in this method.
   *
   * JUCE Doc.:
   *
   * Renders the next block.
   *
   * When this method is called, the buffer contains a number of channels which
   * is at least as great as the maximum number of input and output channels
   * that this filter is using. It will be filled with the filter's input data
   * and should be replaced with the filter's output.
   *
   * So for example if your filter has 2 input channels and 4 output channels,
   * then the buffer will contain 4 channels, the first two being filled with
   * the input data. Your filter should read these, do its processing, and
   * replace the contents of all 4 channels with its output.
   *
   * Or if your filter has 5 inputs and 2 outputs, the buffer will have 5
   * channels, all filled with data, and your filter should overwrite the first
   * 2 of these with its output. But be VERY careful not to write anything to
   * the last 3 channels, as these might be mapped to memory that the host
   * assumes is read-only!
   *
   * Note that if you have more outputs than inputs, then only those channels
   * that correspond to an input channel are guaranteed to contain sensible
   * data - e.g. in the case of 2 inputs and 4 outputs, the first two channels
   * contain the input, but the last two channels may contain garbage, so you
   * should be careful not to let this pass through without being overwritten
   * or cleared.
   *
   * Also note that the buffer may have more channels than are strictly
   * necessary, but you should only read/write from the ones that your filter
   * is supposed to be using.
   *
   * The number of samples in these buffers is NOT guaranteed to be the same
   * for every callback, and may be more or less than the estimated value given
   * to prepareToPlay(). Your code must be able to cope with variable-sized
   * blocks, or you're going to get clicks and crashes!
   *
   * If the filter is receiving a midi input, then the midiMessages array will
   * be filled with the midi messages for this block. Each message's timestamp
   * will indicate the message's time, as a number of samples from the start of
   * the block.
   *
   * Any messages left in the midi buffer when this method has finished are
   * assumed to be the filter's midi output. This means that your filter should
   * be careful to clear any incoming messages from the array if it doesn't
   * want them to be passed-on.
   *
   * Be very careful about what you do in this callback - it's going to be
   * called by the audio thread, so any kind of interaction with the UI is
   * absolutely out of the question. If you change a parameter in here and need
   * to tell your UI to update itself, the best way is probably to inherit from
   * a ChangeBroadcaster, let the UI components register as listeners, and then
   * call sendChangeMessage() inside the processBlock() method to send out an
   * asynchronous message. You could also use the AsyncUpdater class in a
   * similar way.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a7d8c56f45dfd03b507e120eeca7435dd
   *
   * @param     buffer          The audio sample buffer that shall be processed
   *                            in this method.
   *
   * @param     midiMessages    The midi messages incoming for processing.
   */
  void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;

  /**
   * This method currently always returns true.
   *
   * JUCE Doc.:
   *
   * Returns true if the specified channel is part of a stereo pair with its
   * neighbour.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a1de55114a91badc007d1e389a81a14eb
   *
   * @param     index           The index of the channel.
   *
   * @return    true if the specified channel is part of a stereo pair with its
   *            neighbour.
   */
  bool isInputChannelStereoPair(int index) const override;

  /**
   * This method currently always returns true.
   *
   * JUCE Doc.:
   *
   * Returns true if the specified channel is part of a stereo pair with its
   * neighbour.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#aa429d156af1caf829627043615b5ede7
   *
   * @return    true if the specified channel is part of a stereo pair with its
   *            neighbour.
   */
  bool isOutputChannelStereoPair(int index) const override;

  /**
   * This method currently always returns false.
   *
   * TODO: Is this behavior correct?
   *
   * JUCE Doc.:
   *
   * Returns true if a silent input always produces a silent output.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#abbf0119e1ab826b7acbe01eb3f060968
   *
   * @return true if a silent input always produces a silent output.
   */
  bool silenceInProducesSilenceOut() const override;

  /**
   * This method currently always returns 0.0.
   *
   * JUCE Doc.:
   *
   * Returns the length of the filter's tail, in seconds.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a358db82650c6423968091f8b4d22b09a
   *
   * @return the length of the filter's tail, in seconds.
   */
  double getTailLengthSeconds() const override;

  /**
   * This method returns true if the the value of the macro
   * JucePlugin_WantsMidiInput is true.
   *
   * JUCE Doc.:
   *
   * Returns true if the processor wants midi messages.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#ae482a0c2928bfe77de821e6824ffaee6
   *
   * @return true if the processor wants midi messages.
   */
  bool acceptsMidi() const override;

  /**
   * This method returns true if the the value of the macro
   * JucePlugin_ProducesMidiOutput is true.
   *
   * JUCE Doc.:
   *
   * Returns true if the processor produces midi messages.
   *
   * @return true if the processor produces midi messages.
   */
  bool producesMidi() const override;

  /**
   * Returns an instance of the Main_GUI_component class.
   *
   * @see main_gui_component.h
   *
   * JUCE Doc.:
   *
   * Creates the filter's UI.
   *
   * This can return nullptr if you want a UI-less filter, in which case the
   * host may create a generic UI that lets the user twiddle the parameters
   * directly.
   *
   * If you do want to pass back a component, the component should be created
   * and set to the correct size before returning it. If you implement this
   * method, you must also implement the hasEditor() method and make it return
   * true.
   *
   * Remember not to do anything silly like allowing your filter to keep a
   * pointer to the component that gets created - it could be deleted later
   * without any warning, which would make your pointer into a dangler. Use the
   * getActiveEditor() method instead.
   *
   * The correct way to handle the connection between an editor component and
   * its filter is to use something like a ChangeBroadcaster so that the editor
   * can register itself as a listener, and be told when a change occurs. This
   * lets them safely unregister themselves when they are deleted.
   *
   * Here are a few things to bear in mind when writing an editor:
   *
   * Initially there won't be an editor, until the user opens one, or they
   * might not open one at all. Your filter mustn't rely on it being there.
   * An editor object may be deleted and a replacement one created again at any
   * time. It's safe to assume that an editor will be deleted before its filter.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a103fc8a8666b7d31b472e017262be84d
   *
   * @see hasEditor()
   *
   * @return an instance of the Main_GUI_component class.
   */
  AudioProcessorEditor* createEditor() override;

  /**
   * Returns true since this Plugin has a Editor (UI).
   *
   * JUCE Doc.:
   *
   * Your filter must override this and return true if it can create an editor
   * component.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a00be8f595da09ba01d74cb7c52b8fb81
   *
   * @see createEditor()
   *
   * @return true since this Plugin has a Editor (UI).
   */
  bool hasEditor() const override;

  /**
   * Returns the number of parameters.
   *
   * @see source.h
   * @see enum parameter
   *
   * JUCE Doc.:
   *
   * This must return the correct value immediately after the object has been
   * created, and mustn't change the number of parameters later.
   *
   * NOTE! This method will eventually be deprecated! It's recommended that you
   * use the AudioProcessorParameter class instead to manage your parameters.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#ac7b802374ba30b719f34570ab6f07c21
   *
   * @return the number of parameters.
   */
  int getNumParameters() override;

  /**
   * Returns the parameters name identified by the transferred parameterIndex.
   *
   * JUCE Doc.:
   *
   * Returns the name of a particular parameter.
   *
   * NOTE! This method will eventually be deprecated! It's recommended that you
   * use the AudioProcessorParameter class instead to manage your parameters.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a9ae35eca716774ae1fd750d60c52885e
   *
   * @param     parameterIndex          The index of the parameter which name
   *                                    shall be returned.
   *
   * @return the parameters name identified by the parameterIndex.
   **/
  const String getParameterName (int parameterIndex) override;

  /**
   * Returns the parameter value identified by the transferred index.
   *
   * @see source.h
   * @see scene.h
   *
   * JUCE Doc.:
   *
   * Called by the host to find out the value of one of the filter's parameters.
   *
   * The host will expect the value returned to be between 0 and 1.0.
   *
   * This could be called quite frequently, so try to make your code efficient.
   * It's also likely to be called by non-UI threads, so the code in here
   * should be thread-aware.
   *
   * NOTE! This method will eventually be deprecated! It's recommended that you
   * use the AudioProcessorParameter class instead to manage your parameters.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#aa4b04d76a2d80c08f0d762f0fa6b715c
   *
   * @param     index           The index of the parameter which value shall be
   *                            returned.
   *
   * @return the parameter value identified by the transferred index.
   **/
  float getParameter(int index) override;

  /**
   * Return the parameters value identified by the transferred index as
   * a String.
   *
   * If the index is not supported, the Method will return "0.0".
   *
   * JUCE Doc.:
   *
   * Returns the value of a parameter as a text string.
   *
   * NOTE! This method will eventually be deprecated! It's recommended that
   * you use AudioProcessorParameter::getText() instead.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#adfc2bb4a053ea9997dadbb681a636cb0
   *
   * @return    the parameters value identified by the transferred index as
   *            a String.
   **/
  const String getParameterText(int index) override;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // The following methods are own declarations
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++











  virtual void setParameter(int parameterIndex, float newValue) override;





  /**
   * Return the input channel name as a JUCE String.
   **/
  virtual const String getInputChannelName (int channelIndex) const override;

  /**
   * Returns the output channel name as a JUCE String.
   **/
  virtual const String getOutputChannelName (int channelIndex) const override;









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

  void getStateInformation (MemoryBlock& destData);
  void setStateInformation (const void* data, int sizeInBytes);



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
   */
  boost::filesystem::path get_config_file_path();

  std::map<int, std::string> extract_source_names(std::string& message);

  /**
   * This class is declared non copy able.
   */
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Controller)
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
   */
  std::unique_ptr<SSR::SSR_requester> requester;


  std::unique_ptr<SSR::Config> config;

  std::unique_ptr< SSR::Scene > scene;

  //==============================================================================

};


#endif
