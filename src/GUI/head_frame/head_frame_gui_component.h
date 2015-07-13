#ifndef HEAD_FRAME_GUI_COMPONENT_H
#define HEAD_FRAME_GUI_COMPONENT_H

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
#include <memory>

//JUCE Lib
#include <JUCE/JuceHeader.h>

//Own Libs
#include <src/GUI/head_frame/network_gui_component.h>
#include <src/controller.h>

namespace SSR
{
  /**
  * This class represents the head frame GUI component including the
  * 'Network GUI component' and a 'New Source Button'.
  *
  * @author Florian Willich
  */
  class Head_frame_GUI_component
  : public juce::AudioProcessorEditor
  , public juce::Button::Listener
  {

  public:
    /**
     * Constructor which takes a processor object.
     * 
     * @param   processor     The processor.
     */
    Head_frame_GUI_component(Controller* processor);

    /**
     * Deconstructor.
     */
    ~Head_frame_GUI_component();

    /**
     * Like the JUCE documentation say:
     * "The paint() method gets called when a region of a component needs
     * redrawing, either because the component's repaint() method has been
     * called, or because something has happened on the screen that means a
     * section of a window needs to be redrawn."
     *
     * @see             http://www.juce.com/api/classComponent.html#a7cf1862f4af5909ea72827898114a182
     *
     * @param           graphics       the graphics context that must be used
     *                                 to do the drawing operations.
     *
     * @author Florian Willich
     */
    void paint(juce::Graphics& graphics) override;

    /**
     * This method returns the processor to do stuff with it.
     *
     * @return   the processor which is the controller of this software.
     **/
    Controller* getProcessor() const {
      return static_cast<Controller*>(getAudioProcessor());
    }

    /**
     * JUCE Doc.: Called when the button is clicked.
     *
     * @see http://www.juce.com/api/classButton_1_1Listener.html#a81499cef24b7189cd0d1581fd9dc9e14
     *
     * @param           buttonThatWasClicked            The button that was clicked.
     *
     * @author          Florian Willich
     */
    void buttonClicked(juce::Button* buttonThatWasClicked) override;

    /**
     * Returns the current status of the network GUI component.
     *
     * @return          the current status of the network GUI component,
     *                  true means connected, false not.
     *
     * @author  Florian Willich
     */
    bool get_connected() const;

    /**
     * Sets the network GUI component to show whether its connected or not.
     *
     * @param   new_state       The new state on which the network GUI
     *                          component shall be set: true means connected,
     *                          false means not.
     *
     * @author  Florian Willich
     */
    void set_connected(const bool new_state);

  private:
    /**
     * Configures the new source button.
     */
    void configure_new_source_button();

  private:
    /**
    * The network GUI component.
    */
    std::unique_ptr<SSR::Network_gui_component> network_component;

    /**
    * The new source button.
    */
    std::unique_ptr<juce::TextButton> new_source_button;

  };

}

#endif
