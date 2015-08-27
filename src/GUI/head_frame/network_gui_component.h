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

#ifndef NETWORK_GUI_COMPONENT_H
#define NETWORK_GUI_COMPONENT_H

//C++ Libs
#include <memory>

//JUCE Lib
#include <JUCE/JuceHeader.h>

//Own Libs
#include <src/controller.h>

namespace SSR
{

  /**
   * This class represents the Network GUI Component including a button which
   * displays whether the SSRemote VST Plugin is connected to the SSR or not.
   *
   * The 'Connected' button also provides the functionality of connecting to the
   * SSR if it is not and the user clicks on it. Please see issue #6 for more
   * information on why this is currently not well implemented.
   */
  class Network_gui_component
      : public juce::AudioProcessorEditor,
        public juce::ButtonListener,
        public juce::ComponentListener
  {

  public:

    /**
     * Constructor instantiating and configuring the connected_button and
     * registering this class to be a 'Button Listener' - for more information
     * please read the JUCE doc.:
     *
     * http://learn.juce.com/doc/classButton_1_1Listener.php
     *
     * Sets the size of the frame to 138x26 pixels.
     *
     * @param   controller      Controller needed to r/w data.
     *
     * @see http://learn.juce.com/doc/classButton_1_1Listener.php
     */
    Network_gui_component(Controller* controller);

    /**
     * Destructor.
     */
    ~Network_gui_component();

    /**
     * This method returns the processor to do stuff with it.
     *
     * @return   the processor which is the controller of this software.
     **/
    Controller* getProcessor() const {
      return static_cast<Controller*>(getAudioProcessor());
    }

    /**
     * Setter for the connected_button.
     *
     * @param   connected       True means connected, false not.
     */
    void set_connected(const bool connected);

    /**
     * Returns the current status of the connected_button, true means connected,
     * false not.
     *
     * @return  the current status of the connected_button, true means connected,
     *          false not.
     */
    bool get_connected() const;

    /**
     * JUCE Doc.: Called when a button is clicked.
     *
     * @see http://www.juce.com/api/classButton_1_1Listener.html#a81499cef24b7189cd0d1581fd9dc9e14
     *
     * If the button that was clicked is the connected_button, this method
     * checks whether is_connected is true and if not, the controllers connect()
     * method is called. Afterwards, the method checks if the controller is
     * connected and sets the status of the button.
     *
     * TODO: There is no functionality implemented to actually disconnect from
     * the SSR - please see issue #6 for more information.
     *
     * @param           buttonThatWasClicked            The button that was clicked.
     */
    virtual void buttonClicked(Button* button) override;

  private:

    /**
     * The connected button.
     */
    std::unique_ptr<juce::TextButton> connected_button;

    /**
     * GUI status whether the Plugin is connected to the SSR (true) or not (false).
     */
    bool is_connected;

  };

}


#endif
