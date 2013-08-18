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

void module_base::RegisterEvent( const std::string &name, int local_id )
{
  impl.RegisterEvent(name, local_id);
}

bool module_base::SendPreEvent( int local_id, message &m )
{
  return impl.SendPreEvent(local_id, m);
}

void module_base::SendPostEvent( int local_id, message &e )
{
  impl.SendPostEvent(local_id, e);
}

void module_base::Listen( int instance, const std::string &module, const std::string &event )
{
  impl.Listen(instance, module, event);
}

event_source_constructor module_base::GetSourceConstructor() const
{
  return event_source_constructor(impl);
}