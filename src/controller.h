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
   * Currently returns channelIndex + 1.
   *
   * JUCE Doc.:
   *
   * Returns the name of one of the processor's input channels.
   *
   * The processor might not supply very useful names for channels, and this
   * might be something like "1", "2", "left", "right", etc.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a7b08160f29557954c03fd27c07a7380c
   *
   * @param     channelIndex    The index of the channel which input name shall
   *                            be returned.
   *
   * @return channelIndex + 1.
   **/
  const String getInputChannelName(int channelIndex) const override;

  /**
   * Currently returns channelIndex + 1.
   *
   * JUCE Doc.:
   *
   * Returns the name of one of the processor's output channels.
   *
   * The processor might not supply very useful names for channels, and this
   * might be something like "1", "2", "left", "right", etc.
   *
   * Implemented in AudioProcessorGraph, and
   * AudioProcessorGraph::AudioGraphIOProcessor.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#a13811b9a738bd6e807e186b1f9af7c2c
   *
   * @param     channelIndex    The index of the channel which output name shall
   *                            be returned.
   *
   * @return channelIndex + 1
   **/
  const String getOutputChannelName(int channelIndex) const override;

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

  /**
   * Sets the parameter indexed by the transferred parameter parameterIndex
   * to the value of the transferred parameter newValue.
   *
   * The parameterIndex values will index the following parameters:
   *
   * 0 -> X Position
   * 1 -> Y Position
   * 2 -> Gain
   * 3 -> Orientation !Warning! This parameter is currently only readable.
   *      Calling this method to set this parameter will not change the
   *      parameter.
   * 4 -> Mute
   * 5 -> Model Point
   * 6 -> Fixed
   *
   * Please see the Source class for more detailed information on the
   * parameters.
   *
   * @see source.h
   *
   * Furthermore, this method calls the update_ssr(...) method to update the
   * SSR with the correlating update specificator.
   *
   * @see void update_ssr(SSR::Update_specificator specificator)
   *
   * JUCE Doc.:
   *
   * The host will call this method to change the value of one of the filter's
   * parameters.
   *
   * The host may call this at any time, including during the audio processing
   * callback, so the filter has to process this very fast and avoid blocking.
   *
   * If you want to set the value of a parameter internally, e.g. from your
   * editor component, then don't call this directly - instead, use the
   * setParameterNotifyingHost() method, which will also send a message to the
   * host telling it about the change. If the message isn't sent, the host
   * won't be able to automate your parameters properly.
   *
   * The value passed will be between 0 and 1.0.
   *
   * NOTE! This method will eventually be deprecated! It's recommended that you
   * use AudioProcessorParameter::setValue() instead.
   *
   * @param     parameterIndex  Index of the parameter that shall be set to
   *                            the newValue.
   *
   * @param     newValue        The new value to which the parameter shall be
   *                            set to.
   */
  void setParameter(int parameterIndex, float newValue) override;

  /**
   * Currently returns 1.
   *
   * JUCE Doc.:
   *
   * Returns the number of preset programs the filter supports.
   * The value returned must be valid as soon as this object is created, and must
   * not change over its lifetime. This value shouldn't be less than 1.
   *
   * @return    the number of preset programs the filter supports which is
   *            currently set to 1.
   *
   * @see http://www.juce.com/api/classAudioProcessor.html#a510123768a99f32ff4a23d0458e15e13
   */
  int getNumPrograms() override;

  /**
   * Currently returns 0.
   *
   * JUCE Doc.:
   *
   * Returns the number of the currently active program.
   *
   * @return    the number of the currently active program which is currently
   *            always 0.
   *
   * @see http://www.juce.com/api/classAudioProcessor.html
   */
  int getCurrentProgram() override;

  /**
   * Since we do no provide any program (only default), this method does not
   * set the current program to the transferred value of index.
   *
   * JUCE Doc:
   *
   * Called by the host to change the current program.
   *
   * @param     index   The index of the program to which the VST shall be set.
   *
   * @see http://www.juce.com/api/classAudioProcessor.html
   */
  void setCurrentProgram(int index) override;

  /**
   * Since we do not provide any program (only default), this method returns
   * "Default SSRemote VST Program".
   *
   * JUCE Doc:
   *
   * Must return the name of a given program.
   *
   * @param     index   The index of the program which name shall be returned.
   *
   * @return    the name of the given program by the transferred parameter which
   *            will always be "Default SSRemote VST Program".
   *
   * @see http://www.juce.com/api/classAudioProcessor.html
   */
  const juce::String getProgramName(int index) override;

  /**
   * Since we do not provide any program (only default), this method does not
   * set any program name.
   *
   * JUCE Doc.:
   *
   * Called by the host to rename a program.
   *
   * @see http://learn.juce.com/doc/classAudioProcessor.php#accd5bd7b594fbc1a385f7a8b31c7b3f3
   *
   * @param     index   The index of the program which name shall be changed.
   *
   * @param     newName The new name for the program.
   */
  void changeProgramName(int index, const String& newName) override;

  /**
   * TODO: This method must be implemented see issue #10.
   *
   * JUCE Doc.:
   *
   * The host will call this method when it wants to save the filter's internal
   * state.
   *
   * This must copy any info about the filter's state into the block of memory
   * provided, so that the host can store this and later restore it using
   * setStateInformation().
   *
   * Note that there's also a getCurrentProgramStateInformation() method, which
   * only stores the current program, not the state of the entire filter.
   *
   * See also the helper function copyXmlToBinary() for storing settings as XML.
   *
   * @see getStateInformation Doc.
   *      http://learn.juce.com/doc/classAudioProcessor.php#a5d79591b367a7c0516e4ef4d1d6c32b2
   *
   * @see getCurrentProgramStateInformation Doc.
   *      http://learn.juce.com/doc/classAudioProcessor.php#aa8f9774ef205e4b19174f2de7664928f
   *
   * @see copyXmlToBinary Doc.
   *      http://learn.juce.com/doc/classAudioProcessor.php#a6d0c1c945bebbc967d187c0f08b42c4b
   *
   * @see setStateInformation Doc.
   *      http://learn.juce.com/doc/classAudioProcessor.php#a6154837fea67c594a9b35c487894df27
   *
   */
  void getStateInformation(MemoryBlock& destData);

  /**
   * This method must be implemented see issue #11.
   *
   * JUCE Doc.:
   *
   * This must restore the filter's state from a block of data previously
   * created using getStateInformation().
   *
   * Note that there's also a setCurrentProgramStateInformation() method, which
   * tries to restore just the current program, not the state of the entire filter.
   *
   * See also the helper function getXmlFromBinary() for loading settings as XML.
   *
   * @see setStateInformation Doc.
   *      http://learn.juce.com/doc/classAudioProcessor.php#a6154837fea67c594a9b35c487894df27
   *
   * @see setCurrentProgramStateInformation Doc.
   *      http://learn.juce.com/doc/classAudioProcessor.php#ade2c2df3606218b0f9fa1a3a376440a5
   *
   * @see getXmlFromBinary Doc.
   *      http://learn.juce.com/doc/classAudioProcessor.php#af314980ac708cb8802b48317037e5b5b
   */
  void setStateInformation(const void* data, int sizeInBytes);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // The following methods are own declarations
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  /**
   * Returns the current selected source.
   *
   * @return the current selected source.
   */
  SSR::Source get_source() const;

  /**
   * Sets the discrete X position of the current selected source to
   * the transferred position and updates the SSR.
   *
   * @param           position        The new discrete X position the
   *                                  current selected source shall be
   *                                  set to.
   */
  void set_x_position_discrete_of_selected_source(const float position);

  /**
   * Sets the discrete Y position of the current selected source to
   * the transferred position and updates the SSR.
   *
   * @param           position        The new discrete Y position the
   *                                  current selected source shall be
   *                                  set to.
   */
  void set_y_position_discrete_of_selected_source(const float position);

  /**
   * Sets the discrete gain value of the current selected source to the
   * transferred gain and updates the SSR. The additional transferred
   * linear value determines whether the gain value is linear (true) or not
   * (false).
   *
   * @param           gain            The new discrete gain the current
   *                                  selected source shall be set to.
   *
   * @param           linear          Determines if the transferred gain
   *                                  value is linear (true) or not (false).
   */
  void set_gain_discrete_of_selected_source(const float gain, const bool linear);

  /**
   * Sets the discrete mute value of the current selected source to the
   * transferred mute value and updates the SSR.
   *
   * @param           mute            The new value the current selected
   *                                  source parameter mute shall be set to.
   */
  void set_mute_discrete_of_selected_source(const bool mute);

  /**
   * Sets the discrete source model of the current selected source where the
   * transferred parameter point determines whether it is a point source
   * (true) or a plane source (false) and updates the SSR.
   *
   * @param           point           Determines whether the source is point
   *                                  (true) or plane (false).
   */
  void set_model_point_discrete_of_selected_source(const bool point);

  /**
   * Sets the discrete value of the current selected source where the
   * transferred parameter fixed determines whether the source is
   * fixed (true) or movable (false) and updates the SSR.
   *
   * @param           fixed           Determines whether the source shall
   *                                  be fixed (true) or movable (false).
   */
  void set_fixed_discrete_of_selected_source(const bool fixed);

  /**
   * Sets the name of the current selected source to the transferred
   * parameter name and updates the SSR.
   *
   * @param           name            The name the current selected source
   *                                  shall be set to.
   */
  void set_name_of_selected_source(const std::string name);

  /**
   * Sets the properties file of the current selected source to the
   * transferred parameter prop_file and updates the SSR.
   *
   * @param           prop_file       The properties file the current
   *                                  selected source shall be set to.
   */
  void set_properties_file_of_selected_source(const std::string value);

  /**
   * Sets the jackport of the current selected source to the transferred
   * parameter jackport and updates the SSR.
   *
   * @param           jackport        The jackport the current selected
   *                                  source shall be set to.
   */
  void set_jackport_of_selected_source(const std::string jackport);

  /**
   * Changes the current selected source to the source with the transferred
   * id and returns if the selection was successful.
   *
   * @param           id              The id of the source that shall be
   *                                  selected.
   *
   * @return          true if the selection was successful, false otherwise.
   */
  bool select_source(const int id);

  /**
   * Creates a new source with a random generated name which will be composed
   * as follows:
   *
   * SourceXXXXX
   *
   * X -> Any character from A to Z (capitalized).
   *
   * After creating the new source, the new source will be the current selected
   * source and the SSR will be updated.
   */
  void new_source();

  /**
   * This method reads the incoming message from the SSR server, interprets
   * them and updates the members if there have been any request of doing so
   * from the SSR server.
   *
   * @return       if there was any message from the SSR server to interpret.
   **/
  bool read_ssr_incoming_message();

  /**
   * This method will try to connect to the SSR with the data given by the
   * XML config file (which data will be loaded every time this method is
   * called).
   */
  void connect();

  /**
   * Returns true if the connection to SSR is established.
   *
   * @return true if the connection to SSR is established.
   **/
  bool is_connected_to_ssr() const;

  /**
   * Returns true if the UI needs update.
   *
   * @return true if the UI needs update.
   **/
  bool ui_needs_update() const;

  /**
   * Sets the ui_update_flag to true for requesting a UI update.
   **/
  void ui_request_update();

  /**
   * Clears the ui_update_flag by setting it tp false.
   **/
  void ui_clear_update_flag();

  /**
   * This method returns all Jack Ports specified by the flags. If there are no
   * jackports available, the method will return a vector with one element
   * which content is "No Jackport available.".
   *
   * Furthermore, the method will log an error an error occurs.
   *
   * @param    flags       Flags to specify which Jack Ports shall be returned.
   *                       See JackPortFlags (jack/types.h) for all flags you can
   *                       set.
   *
   * @return   all jackports specified by the flags.
   **/
  std::vector<std::string> get_all_jack_ports(const unsigned long flags);

  /**
   * This method will update the SSR by composing a string with all information
   * needed for updating the parameters specified by the specificator.
   *
   * Finally, the method will send the new composed message to the SSR.
   *
   * @see update_specificator.h
   * @see ssr_requester.h
   *
   * @param     specificator    The specificator specifying the parameters
   *                            which shall be updated.
   */
  void update_ssr(SSR::Update_specificator specificator);

  /**
   * Creates a vector with the sources ids and names and returns it.
   *
   * @return the sources ids and names.
   */
  std::shared_ptr< std::vector< std::pair<unsigned int, std::string> > > get_source_ids_and_names();

private:

  /**
   * Sends the message_to_ssr to the SSR and sets the message_to_ssr to empty
   * string.
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

  /**
   * The config for this VST Plugin.
   */
  std::unique_ptr<SSR::Config> config;

  /**
   * The scene with all related sources and additional information.
   */
  std::unique_ptr< SSR::Scene > scene;

};


#endif
