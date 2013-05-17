#include "module.h"

using namespace ed;

void module::RegisterQueryCallback( query_callback_type q, int source_instance, std::string event, std::string module )
{
  int module_global_id = gw.RegisterName(MODULES, module);
  int event_global_id = gw.RegisterName(EVENTS, event);

  event_source es;
  es.event = event_global_id;
  es.module = module_global_id;
  es.instance = source_instance;
  RegisterQueryCallback(q, es);
}

void module::RegisterQueryCallback( query_callback_type q, event_source source )
{
  callback_entry<query_callback_type> t;
  t.callback = q;
  t.source = source;
  QueryCallbacks.push_back(t);
  gw.Listen(source.instance, id, source.module, source.event);
}

void module::RegisterEventCallback( event_callback_type q, int source_instance, std::string event, std::string module )
{
  int module_global_id = gw.RegisterName(MODULES, module);
  int event_global_id = gw.RegisterName(EVENTS, event);

  event_source es;
  es.event = event_global_id;
  es.module = module_global_id;
  es.instance = source_instance;
  RegisterEventCallback(q, es);
}

void module::RegisterEventCallback( event_callback_type q, event_source source )
{
  callback_entry<event_callback_type> t;
  t.callback = q;
  t.source = source;
  EventCallbacks.push_back(t);
  gw.Listen(source.instance, id, source.module, adapter.ToGlobal(source.event));
}


void module::EventReciever( const message &m )
{
  const event_notification en = m;
  std::vector<callback_entry<event_callback_type>>::const_iterator
    i = EventCallbacks.begin(),
    e = EventCallbacks.end();
  while (i != e)
  {
    const callback_entry<event_callback_type> &t = *i++;
    if (en.source == t.source)
      (this->*t.callback)(event_context(adapter.ToLocal(m.event), en.source, m.payload));
  }
}

bool module::Query( const message &m )
{
  const event_notification en = m;
  std::vector<callback_entry<query_callback_type>>::const_iterator
    i = QueryCallbacks.begin(),
    e = QueryCallbacks.end();
  while (i != e)
  {
    const callback_entry<query_callback_type> &t = *i++;
    if (en.source == t.source)
      if (!(this->*t.callback)(event_context(adapter.ToLocal(m.event), en.source, m.payload)))
        return false;
  }
  return true;
}