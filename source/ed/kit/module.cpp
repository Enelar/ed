#include "module.h"
#include "../names/reserved.h"

using namespace ed;

module::module( int _id, gateway &_gw )
  : id(_id), gw(_gw)
{
}

module::module( const std::string &name, gateway &_gw )
  : gw(_gw)
{
  gw.CreateModule(name, this);
}

void module::RegisterEvent( std::string name, int local_id )
{
  int global_id = gw.RegisterEvent(name);
  adapter.AddPair(local_id, global_id);
}

event_result module::SendEvent( int local_id, EVENT_RING query_max_ring, EVENT_RING notify_max_ring )
{
  return SendEvent(local_id, buffer(0), query_max_ring, notify_max_ring);
}

event_result module::SendEvent( int local_id, buffer payload, EVENT_RING query_max_ring, EVENT_RING notify_max_ring )
{
  event_notification e(payload);
  e.target_module = reserved::module::BROADCAST;
  e.source.event = adapter.ToGlobal(local_id);
  e.source.module = id;
  e.source.instance = reserved::module::BROADCAST;
  
  message m = e;
  m.flags.state = PRE_QUERY;
  m.flags.ring = query_max_ring;

  bool result = SendPreEvent(local_id, m);
  return event_result(m, *this, local_id, result, notify_max_ring);
}

bool module::SendPreEvent( int local_id, message &m )
{
  if (pre_listeners.size() > (unsigned)local_id && pre_listeners[local_id].modules.size() > 0)
  { // RING 0
    std::list<int>::const_iterator
      i = pre_listeners[local_id].modules.begin(),
      e = pre_listeners[local_id].modules.end();
    while (i != e)
    {
      if (!gw.QueryModule(*i, m))
        return false;
      i++;
    }
  }

  return gw.PreNotify(m);
}

void module::SendPostEvent( int local_id, message &e )
{
  gw.PostNotify(e);
}

void module::Listen( int instance, std::string module, std::string event )
{
  //gw.CreateModule
}