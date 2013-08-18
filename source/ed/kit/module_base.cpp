#include "module.h"

using namespace ed;

module_base::module_base( int _id, gateway &_gw )
#pragma warning(disable: 4355)
  : impl(*NEW module_impl(*this, _id, _gw))
#pragma warning(default: 4355)
{
}

module_base::module_base( const std::string &name, gateway &_gw )
#pragma warning(disable: 4355)
  : impl(*NEW module_impl(*this, name, _gw))
#pragma warning(default: 4355)
{
}

module_base::~module_base()
{
  delete &impl;
}

void module_base::EventReciever( const message &m )
{
  impl.EventReciever(m);
}

bool module_base::Query( const message &m )
{
  return impl.Query(m); 
}