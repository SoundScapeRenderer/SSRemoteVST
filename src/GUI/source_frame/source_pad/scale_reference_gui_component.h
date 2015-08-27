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

//C++ Libs
#include <sstream>

//JUCE Include
#include <JUCE/JuceHeader.h>

namespace SSR
{

  /**
   * This class represents the scale reference GUI component for illustrating
   * the ratio of the grid where the source GUI component moves on.
   *
   * This is done by computing the meters per pixel represented in the GUI (grid)
   * and displaying a bar with its represented length shown in meters.
   */
  class Scale_reference_GUI_component
      : public juce::Component
  {

  public:

    /**
     * Constructor setting the size of this GUI component to 100x12 pixels.
     *
     * The transferred reference_pixels represent the count of pixels the range
     * is referring to when calculating the current scale reference.
     *
     * The transferred reference_range represent the range in meters the
     * reference_pixels represent in pixels.
     */
    Scale_reference_GUI_component(unsigned int reference_pixels, double reference_range);

    /**
     * Destructor
     */
    ~Scale_reference_GUI_component();

    /**
     * Draws the GUI component.
     *
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
     */
    void paint(Graphics& graphics) override;

    /**
     * Sets the reference_range to the new_reference_range, computes the new
     * current_reference (meter per pixel) and repaints the component.
     *
     * @param           new_reference_range     The new reference range in meters.
     */
    void set_reference_range(const double new_reference_range);

  private:

    /**
     * Computes the current reference.
     */
    void compute_current_reference();

  private:

    /**
     * The count of pixels referenced to.
     */
    unsigned int reference_pixels;

    /**
     * The range in meters the refernce_pixels are representing.
     */
    double reference_range;

    /**
     * The current reference.
     */
    double current_reference;

    /**
     * The size of the reference bar.
     */
    float reference_bar_size;

    /**
     * Stringstream object.
     */
    std::unique_ptr<std::ostringstream> oss;

  };

}

#endif
