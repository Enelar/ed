#include "module.h"
#include "../names/reserved.h"

using namespace ed;

module::module( int _id, gateway &_gw )
#pragma warning(disable: 4355)
  : impl(*NEW module_impl(*this, _id, _gw))
#pragma warning(default: 4355)
{
}

module::module( const std::string &name, gateway &_gw )
#pragma warning(disable: 4355)
  : impl(*NEW module_impl(*this, name, _gw))
#pragma warning(default: 4355)
{
}

module::~module()
{
  delete &impl;
}

void module::RegisterEvent( std::string name, int local_id )
{
  impl.RegisterEvent(name, local_id);
}

event_result module::SendEvent( int local_id, EVENT_RING query_max_ring, EVENT_RING notify_max_ring )
{
  return impl.SendEvent(local_id, query_max_ring, notify_max_ring);
}

event_result module::SendEvent( int local_id, buffer payload, EVENT_RING query_max_ring, EVENT_RING notify_max_ring )
{
  return impl.SendEvent(local_id, payload, query_max_ring, notify_max_ring);
}

bool module::SendPreEvent( int local_id, message &m )
{
  return impl.SendPreEvent(local_id, m);
}

void module::SendPostEvent( int local_id, message &e )
{
  impl.SendPostEvent(local_id, e);
}

void module::Listen( int instance, std::string module, std::string event )
{
  impl.Listen(instance, module, event);
}