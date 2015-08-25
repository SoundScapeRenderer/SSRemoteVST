#ifndef __JUCE_HEADER_3AFE319E6C7B8A70__
#define __JUCE_HEADER_3AFE319E6C7B8A70__

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

//Own Classes
#include <src/controller.h>
#include <src/GUI/head_frame/head_frame_gui_component.h>
#include <src/GUI/source_frame/source_frame_gui_component.h>

//C++ Libs
#include <ctime>
#include <string>
#include <map>
#include <memory>

//JUCE Lib
#include <JUCE/JuceHeader.h>


/**
* This class represents the graphical user interface (GUI) of the VST-Plugin.
* The GUI is splitted in a 'Head' and 'Source' part.
*
* The 'Head' part includes the 'Network Component' and the 'New Source' Button.
*
* The 'Source' part includes the source selection GUI element, all the source
* properties (Name, Jackport, Model, Properties File, Azimuth, Mute, Fixed and
* Gain) and also a pad representing the sources spatial position.
**/
class Main_GUI_component
    : public AudioProcessorEditor
    , public Timer
{
    
public:

  /**
   * Constructor creating a window with the size of 900 to 600 pixels
   * and starting an updating timer with 10 ms for the updating interval.
   *
   * @param      controller             The controller of this application.
   */
  Main_GUI_component(Controller* controller);

  /**
   * Destructor.
   */
  ~Main_GUI_component();

  /**
   * Inherited from the JUCE Timer Class.
   *
   * Like the JUCE documentation say: "The user-defined callback routine that
   * actually gets called periodically."
   *
   * Currently, this method calls the processors method to read the incoming
   * messages and then sets all the UI elements to the new values held by the
   * processor if there have been any changes.
   **/
  virtual void timerCallback() override;

  /**
   * This method returns the processor to do stuff with it.
   *
   * @return   the processor which is the controller of this software.
   **/
  Controller* getProcessor() const {
    return static_cast<Controller*>(getAudioProcessor());
  }

  /**
   * Like the JUCE documentation say:
   * "The paint() method gets called when a region of a component needs
   * redrawing, either because the component's repaint() method has been
   * called, or because something has happened on the screen that means a
   * section of a window needs to be redrawn."
   *
   * @param           graphics          The graphics context that must be used
   *                                    to do the drawing operations.
   */
  virtual void paint(juce::Graphics& graphics) override;

private:
    
    /**
     * This is the head frame of the GUI. Representing all GUI elements
     * placed in the head.
     */
    juce::ScopedPointer<SSR::Head_frame_GUI_component> head_frame;

    /**
     * This is the source frame of the GUI. Representing all GUI elements
     * relating the source.
     */
    juce::ScopedPointer<SSR::Source_frame_gui_component> source_frame;

    /**
     * This class is declared non copy able.
     */
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main_GUI_component);

};

#endif
