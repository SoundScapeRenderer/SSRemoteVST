#ifndef UPDATE_SPECIFICATOR_H
#define UPDATE_SPECIFICATOR_H

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

namespace SSR
{

  /**
   * This class helps to specify which parameter has to be updated by the SSR.
   */
  class Update_specificator
  {

  public:

    /**
     * The specificators:
     *
     * - gain
     * - position
     * - mute
     * - fixed
     * - model
     * - properties_file
     * - port
     * - name
     * - new_source
     */
    enum Specificators {
      gain,
      position,
      mute,
      fixed,
      model,
      properties_file,
      port,
      name,
      new_source
    };

    /**
     * Constructor setting the member specificator to the transferred
     * specificator.
     */
    Update_specificator(Specificators specificator);

    /**
     * Destructor.
     */
    ~Update_specificator();

    /**
     * Returns the specificator which has be set during construction.
     *
     * @see Specificators
     */
    Specificators get_spec() const;

  private:

    /**
     * The specificator.
     */
    Specificators specificator;

  };

}


#endif
