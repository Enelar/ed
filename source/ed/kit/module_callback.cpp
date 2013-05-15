#include "module.h"

using namespace ed;

void module::RegisterQueryCallback( query_callback_entry_type q, event_source source )
{
  callback_entry<query_callback_entry_type> t;
  t.callback = q;
  t.source = source;
  QueryCallbacks.push_back(t);
}

void module::RegisterEventCallback( event_callback_entry_type q, event_source source )
{
  callback_entry<event_callback_entry_type> t;
  t.callback = q;
  t.source = source;
  EventCallbacks.push_back(t);
}


void module::EventReciever( const message &m )
{
  const event_notification en = m;
  std::vector<callback_entry<event_callback_entry_type>>::const_iterator
    i = EventCallbacks.begin(),
    e = EventCallbacks.end();
  while (i != e)
  {
    const callback_entry<event_callback_entry_type> &t = *i++;
    if (en.source == t.source)
      (this->*t.callback)(adapter.ToLocal(m.event), en.source, m.payload);
  }
}

bool module::Query( const message &m )
{
  const event_notification en = m;
  std::vector<callback_entry<query_callback_entry_type>>::const_iterator
    i = QueryCallbacks.begin(),
    e = QueryCallbacks.end();
  while (i != e)
  {
    const callback_entry<query_callback_entry_type> &t = *i++;
    if (en.source == t.source)
      if (!(this->*t.callback)(adapter.ToLocal(m.event), en.source, m.payload))
        return false;
  }
  return true;
}