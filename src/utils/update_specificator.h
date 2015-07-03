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

  class Update_specificator
  {

  public:

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

    Update_specificator(Specificators spec);

    ~Update_specificator();

    Specificators get_spec() const;

  private:
    Specificators spec;

  };

}


#endif
