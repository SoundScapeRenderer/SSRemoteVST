#ifndef SCALE_REFERENCE_GUI_COMPONENT
#define SCALE_REFERENCE_GUI_COMPONENT

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

//JUCE Include
#include <JuceLibraryCode/JuceHeader.h>

namespace SSR
{

  class Scale_reference_GUI_component : public juce::Component
  {

  public:
    Scale_reference_GUI_component(unsigned int reference_pixels, double reference_range);
    ~Scale_reference_GUI_component();

    /**
     * JUCE Dok:
     *
     * <i>[...]
     *
     * The paint() method gets called when a region of a component needs
     * redrawing, either because the component's repaint() method has been called,
     * or because something has happened on the screen that means a section of a
     * window needs to be redrawn.
     *
     * [...]
     *
     * You should never need to call this method directly - [...]</i>
     *
     * @param           graphics        the graphics context that must be used to
     *                                  do the drawing operations.
     *
     * @author Florian Willich
     */
    void paint(Graphics& graphics) override;

    void set_reference_range(const double new_reference_range);

  private:
    void compute_current_reference();

  private:
    unsigned int reference_pixels;
    double reference_range;
    double current_reference;
    float reference_bar_size;

  };

}

#endif
