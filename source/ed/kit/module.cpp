#include "module.h"
#include "../names/reserved.h"

using namespace ed;

module::module( int _id, gateway &_gw ) : module_base(_id, _gw)
{
}

module::module( const std::string &name, gateway &_gw ) : module_base(name, _gw)
{
}

module::~module()
{
}

event_result module::SendEvent( int local_id, EVENT_RING query_max_ring, EVENT_RING notify_max_ring )
{
  return impl.SendEvent(local_id, query_max_ring, notify_max_ring);
}

event_result module::SendEvent( int local_id, buffer payload, EVENT_RING query_max_ring, EVENT_RING notify_max_ring )
{
  return impl.SendEvent(local_id, payload, query_max_ring, notify_max_ring);
}