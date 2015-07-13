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

//Juce Libs
#include <JUCE/JuceHeader.h>

namespace SSR
{

  class Zoom_GUI_component
      : public juce::Component
      , public juce::TextButton::Listener
      , public juce::ChangeBroadcaster
  {

  public:

    Zoom_GUI_component();

    ~Zoom_GUI_component();

    void buttonClicked(juce::Button* textButton) override;

    double get_current_range() const;

  private:
    /**
     * Look up method for the range.
     * 
     * Current table:
     *
     * 0 -> 0.4 
     * 1 -> 1 
     * 2 -> 3 
     * 3 -> 5 
     * 4 -> 10 
     * 5 -> 20 
     * 6 -> 50 
     * 7 -> 200 
     * 8 -> 500 
     * 9 -> 2000
     *
     * Why we implemented a look up table is simply because there is no
     * function that represents that concrete ranges and a look up table
     * seemed to fit the purpose.
     *
     * Returns the above written values for the above written zoom factors.
     * If the zoom_factor is not between 0 and 9, the method returns the 
     * value for zoom factor 0!
     *
     * @param     zoom_factor     The zoom factor which determines the range,
     *                            should be between 0 and 9.
     *
     * @return    the above written values for the above written zoom factors.
     *            If the zoom_factor is not between 0 and 9, the method returns
     *            the value for zoom factor 0!
     *
     * @author    Florian Willich
     */
    double look_up_range(const unsigned int zoom_factor);

  private:
    std::unique_ptr<juce::TextButton> zoom_in_button;
    std::unique_ptr<juce::TextButton> zoom_out_button;
    unsigned int zoom_factor;
    double current_range;

  };

}


#endif
