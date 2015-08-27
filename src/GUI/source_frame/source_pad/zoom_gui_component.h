#ifndef ZOOM_GUI_COMPONENT_H
#define ZOOM_GUI_COMPONENT_H

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
#include <array>

//Juce Libs
#include <JUCE/JuceHeader.h>

namespace SSR
{

  /**
   * This class represents the Zoom GUI Component.
   *
   * This component enables the user to zoom in and zoom out of the source
   * grid.
   *
   * Each zoom factor has a related representation in meters which is the
   * range the grid will represent. For zooming in and out we have implemented
   * a look up table.
   *
   * Why we implemented a look up table is simply because there is no
   * function that represents that concrete ranges and a look up table
   * seemed to fit the purpose.
   */
  class Zoom_GUI_component
      : public juce::Component
      , public juce::TextButton::Listener
      , public juce::ChangeBroadcaster
  {

  public:

    /**
     * Constructor initialising the zoom_factor with 3 and the
     * zoom_look_up_table with the following values:
     *
     * index: 0 -> value: 0.4
     * index: 1 -> value: 1
     * index: 2 -> value: 3
     * index: 3 -> value: 5
     * index: 4 -> value: 10
     * index: 5 -> value: 20
     * index: 6 -> value: 50
     * index: 7 -> value: 200
     * index: 8 -> value: 500
     * index: 9 -> value: 2000
     *
     * Sets the current_range by looking it up with the current zoom_factor.
     *
     * Sets the size of this GUI component to 25x50 pixels.
     */
    Zoom_GUI_component();

    /**
     * Destructor.
     */
    ~Zoom_GUI_component();

    /**
     * This method is called when a button of this GUI component is clicked.
     *
     * For more information please read:
     *
     * http://learn.juce.com/doc/classButton_1_1Listener.php#a81499cef24b7189cd0d1581fd9dc9e14
     *
     * @see http://learn.juce.com/doc/classButton_1_1Listener.php#a81499cef24b7189cd0d1581fd9dc9e14
     *
     * If the button that was clicked is the zoom_in_button, the zoom_factor
     * will be decreased by 1 (if the zoom_factor is already 0 the zoom_factor
     * will not be decreased).
     *
     * If the button that was clicked is the zoom_out_button, the zoom_factor
     * will be increased by 1 (if the zoom_factor is already 9 the zoom-factor
     * will not be increased).
     *
     * After decreasing or increasing, the current range will be computed and
     * change message send.
     *
     * @param   textButton      The text button that was clicked.
     */
    void buttonClicked(juce::Button* textButton) override;

    /**
     * Returns the current range.
     *
     * @return the current range.
     */
    double get_current_range() const;

  private:
    /**
     * Look up method for the range.
     *
     * Returns the above written values for the above written zoom factors
     * (the index is equal to the zoom factor).
     *
     * If the zoom_factor is greater than 9 the method will return the value
     * for the zoom factor 9.
     *
     * @see Zoom_GUI_component()
     *
     * @param     zoom_factor     The zoom factor which determines the range,
     *                            If the zoom_factor is greater than 9 the
     *                            method will return the value for the zoom
     *                            factor 9.
     *
     * @return  the above written values for the above written zoom factors.
     *          If the zoom_factor is greater than 9 the method will return
     *          the value for the zoom factor 9.
     */
    double look_up_range(const unsigned int zoom_factor);

  private:

    /**
     * The zoom in button.
     */
    std::unique_ptr<juce::TextButton> zoom_in_button;

    /**
     * The zoom out button.
     */
    std::unique_ptr<juce::TextButton> zoom_out_button;

    /**
     * The zoom factor.
     */
    unsigned int zoom_factor;

    /**
     * The current range represented by the zoom factor in meters.
     */
    double current_range;

    /**
     * The look up table for the ranges for each zoom factor.
     */
    std::array<double, 10> zoom_look_up_table;

  };

}


#endif
