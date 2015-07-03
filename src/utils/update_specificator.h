#ifndef UPDATE_SPECIFICATOR_H
#define UPDATE_SPECIFICATOR_H

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
