//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

//C++ Libs
#include <memory>

//Own Libs
#include <src/GUI/head_frame/network_gui_component.h>
#include <src/controller.h>

SSR::Network_gui_component::Network_gui_component(Controller* processor)
: AudioProcessorEditor(processor)
, connected_button(new juce::TextButton("connected_button"))
, is_connected(false)
{

  addAndMakeVisible(*connected_button);

  connected_button->addListener(this);
  connected_button->setBounds(0, 0, 138, 25);
  connected_button->setButtonText(TRANS("Connected"));

  setSize(138, 26);
}

SSR::Network_gui_component::~Network_gui_component()
{
  //This unregisters all children from the component
  removeAllChildren();
  connected_button = nullptr;
}

void SSR::Network_gui_component::set_connected(const bool new_state)
{
  is_connected = new_state;
  connected_button->setToggleState(is_connected, juce::dontSendNotification);
}

bool SSR::Network_gui_component::get_connected() const
{
  return is_connected;
}

void SSR::Network_gui_component::buttonClicked(Button* button)
{

  if (button == connected_button.get()) {
      Controller* processor = getProcessor();

      if (!is_connected) {
          processor->connect();
      }

      is_connected = processor->is_connected_to_ssr();

      connected_button->setToggleState(is_connected, juce::dontSendNotification);
  }

}
