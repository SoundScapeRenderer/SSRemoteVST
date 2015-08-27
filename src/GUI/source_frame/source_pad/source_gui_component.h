#ifndef SOURCE_GUI_COMPONENT_H
#define SOURCE_GUI_COMPONENT_H

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

//JUCE Lib
#include <JUCE/JuceHeader.h>

//C++ Libs
#include <memory>

namespace SSR
{

  /**
   * This class represents the Source GUI Component.
   *
   * The Source GUI Component is graphically represented as a circle similar
   * to the source GUI component in the SSR.
   */
  class Source_gui_component
      : public juce::Component
  {

  public:

    /**
     * Constructor initialising the radius with 20.0. Sets the size of the
     * component to 40x40 pixels.
     */
    Source_gui_component();

    /**
     * Constructor initialising the radio with width_and_height / 2. Sets the
     * size of the component to width_and_height x width_and_height pixels.
     *
     * @param   width_and_height        The width and height of the GUI
     *                                  component.
     */
    Source_gui_component(const unsigned int width_and_height);

    /**
     * Destructor.
     */
    ~Source_gui_component();

    /**
     * Draws the component.
     *
     * For more information on this method please read the JUCE documentaion:
     *
     * http://learn.juce.com/doc/classComponent.php#a7cf1862f4af5909ea72827898114a182
     *
     * @see http://learn.juce.com/doc/classComponent.php#a7cf1862f4af5909ea72827898114a182
     *
     * @param   graphics        The graphics context that must be used to do
     *                          the drawing operations.
     */
    void paint(juce::Graphics& graphics) override;

    /**
     * Returns the radius of the source.
     */
    float get_radius() const;

  private:

    /**
     * Draws the background of the component.
     */
    void draw_background(juce::Graphics& graphics);

  private:

    /**
     * Radius of the circle (representing the source).
     */
    float radius;

  };


}

#endif
