#include <src/utils/update_specificator.h>

SSR::Update_specificator::Update_specificator(Specificators spec)
: spec(spec)
{

}

SSR::Update_specificator::~Update_specificator()
{

}

SSR::Update_specificator::Specificators SSR::Update_specificator::get_spec() const
{
  return spec;
}
