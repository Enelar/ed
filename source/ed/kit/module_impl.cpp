#include "module.h"
#include "../names/reserved.h"

using namespace ed;

module_impl::module_impl( module_base &_m, int _id, gateway &_gw )
  : id(_id), gw(_gw), m(_m)
{
}

module_impl::module_impl( module_base &_m, const std::string &name, gateway &_gw )
  : gw(_gw), m(_m)
{
  gw.CreateModule(name, *this);
}

module_impl::~module_impl()
{
  for (unsigned int i = 0; i < QueryCallbacks.size(); ++i)
    if (QueryCallbacks[i])
      throw_message("You forget to unregister modules handler");

  for (unsigned int i = 0; i < EventCallbacks.size(); ++i)
    if (EventCallbacks[i])
      throw_message("You forget to unregister modules handler");
}

void module_impl::RegisterEvent( const std::string &name, int local_id )
{
  int global_id = gw.RegisterEvent(name);
  adapter.AddPair(local_id, global_id);
}

event_result module_impl::SendEvent( int local_id, EVENT_RING query_max_ring, EVENT_RING notify_max_ring )
{
  return SendEvent(local_id, buffer(0), query_max_ring, notify_max_ring);
}

event_result module_impl::SendEvent( int local_id, buffer payload, EVENT_RING query_max_ring, EVENT_RING notify_max_ring )
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
  return event_result(m, this->m, local_id, result, notify_max_ring);
}

bool module_impl::SendPreEvent( int local_id, message &m )
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

void module_impl::SendPostEvent( int local_id, message &e )
{
  gw.PostNotify(e);
}

void module_impl::Listen( int instance, const std::string &module, const std::string &event )
{
  //gw.CreateModule
}

void module_impl::AddPreHandler( base_pre_callback_entry *obj )
{
  QueryCallbacks.push_back(obj);
  gw.Listen(obj->source.instance, id, obj->source.module, adapter.ToGlobal(obj->source.event));
}
void module_impl::AddPostHandler( base_post_callback_entry *obj )
{
  EventCallbacks.push_back(obj);
  gw.Listen(obj->source.instance, id, obj->source.module, adapter.ToGlobal(obj->source.event));
}