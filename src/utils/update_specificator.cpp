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

#include <src/utils/update_specificator.h>

SSR::Update_specificator::Update_specificator(Specificators specificator)
: specificator(specificator)
{

}

SSR::Update_specificator::~Update_specificator()
{

}

SSR::Update_specificator::Specificators SSR::Update_specificator::get_spec() const
{
  return specificator;
}
