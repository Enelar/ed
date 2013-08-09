#include "module.h"

using namespace ed;
            

void module::EventReciever( const message &m )
{
  const event_source en = static_cast<event_notification>(m);
  event_source en0 = en;
  en0.event = reserved::event::BROADCAST;
  std::vector<base_post_callback_entry>::const_iterator
    i = EventCallbacks.begin(),
    e = EventCallbacks.end();
  while (i != e)
  {
    const base_post_callback_entry &t = *i++;
    if (en == t.source || en0 == t.source)
      t.callback->FarCall(
        event_context<>(
          adapter.ToLocal(m.event),
          en, NEW event_data(m)
            ));
  }
}

bool module::Query( const message &m )
{
  const event_notification en = m;
  std::vector<base_pre_callback_entry>::const_iterator
    i = QueryCallbacks.begin(),
    e = QueryCallbacks.end();
  while (i != e)
  {
    const base_pre_callback_entry &t = *i++;
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