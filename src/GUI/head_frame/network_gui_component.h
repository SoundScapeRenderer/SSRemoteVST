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

//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

//Own Libs
#include <src/controller.h>

namespace SSR
{

  class Network_gui_component : public juce::AudioProcessorEditor,
  public juce::ButtonListener,
  public juce::ComponentListener
  {
  public:
    Network_gui_component(Controller* processor);

    ~Network_gui_component();

    /**
     * This method returns the processor to do stuff with it.
     *
     * @return   the processor which is the controller of this software.
     **/
    Controller* getProcessor() const {
      return static_cast<Controller*>(getAudioProcessor());
    }

    void set_connected(const bool new_state);

    bool get_connected() const;

    void message_incoming(const bool is_incoming);

    virtual void buttonClicked(Button* button) override;

  private:
    std::unique_ptr<juce::TextButton> connected_button;
    bool is_connected;

  };

}


#endif
