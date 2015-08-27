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
     * Constructor initialising
     *
     * Fills the zoom_look_up_table with the following values:
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
     */
    Zoom_GUI_component();

    ~Zoom_GUI_component();

    void buttonClicked(juce::Button* textButton) override;

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
    std::unique_ptr<juce::TextButton> zoom_in_button;
    std::unique_ptr<juce::TextButton> zoom_out_button;
    unsigned int zoom_factor;
    double current_range;

    std::array<double, 10> zoom_look_up_table;

  };

}


#endif
