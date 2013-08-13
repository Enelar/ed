#include "module.h"

using namespace ed;


bool BroadCastPatten( const event_source &filter, event_source catched )
{
  if (filter == catched)
    return true;
  if (filter.instance && filter.instance != catched.instance)
    return false;
  if (filter.module && filter.module != catched.module)
    return false;
  if (filter.event && filter.event != catched.event)
    return false;
  return true;
}

void module_impl::EventReciever( const message &m )
{
  const event_source en = static_cast<event_notification>(m);
  event_source en0 = en;
  std::vector<base_post_callback_entry *>::const_iterator
    i = EventCallbacks.begin(),
    e = EventCallbacks.end();

  event_context<> data(
          adapter.ToLocal(m.event),
          en, NEW event_data(m)
            );
  while (i != e)
  {
    const base_post_callback_entry &t = **i++;
    
    if (BroadCastPatten(t.source, en))
      t.callback->FarCall(data);
  }
}

bool module_impl::Query( const message &m )
{
  const event_notification en = m;
  std::vector<base_pre_callback_entry *>::const_iterator
    i = QueryCallbacks.begin(),
    e = QueryCallbacks.end();
  while (i != e)
  {
    const base_pre_callback_entry &t = **i++;
    if (en.source == t.source)
      if (t.callback->FarCall(
          event_context<>(
            adapter.ToLocal(m.event),
            en.source, 
              NEW event_data(m))))
        return false;
  }
  return true;
}