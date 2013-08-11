#include "gateway.h"
#include "../messages/register.h"
#include "../names/reserved.h"
#include "../3party/win/utils.h"

using namespace ed;
using namespace ed::com;

gateway_impl::gateway_impl( gateway &_gw, com::abstract_connection &_c )
  : c(_c), gw(_gw)
{
}

module &gateway_impl::CreateModule( std::string name )
{
  return *NEW module(name, gw);
}

int gateway_impl::RegisterName( NAME_TYPE nt, std::string name )
{
  if (!name.length())
    switch (nt)
    {
    case EVENTS:
      return reserved::event::BROADCAST;
    case MODULES:
      return reserved::module::BROADCAST;
    default:
      dead_space();
    }

  register_message rm(nt, name);
  c.SendRegister(rm);

  message *m;
  while (true)
  {
    while (c.Incoming() < 1)
      ed::Sleep(1);
    m = c.Get();
    throw_assert(m);
    if (m->event == reserved::event::EVENT_REGISTER)
      break;
    delayed_messages.push_back(*m);
    delete m;
  }
  event_notification e = *m;
  delete m;
  throw_assert(e.source.event == reserved::event::EVENT_REGISTER);
  throw_assert(e.payload_size == 4);

  instance = e.source.instance;
  return *(int *)e.payload;
}

void gateway_impl::CreateModule( std::string name, module *const ret )
{
  ret->id = RegisterName(MODULES, name);
  local_modules.AddModule(ret, ret->id);
}


int gateway_impl::RegisterEvent( std::string name )
{
  return RegisterName(EVENTS, name);
}

bool gateway_impl::PreNotify( const message &e )
{
  if (e.flags.ring == 0)
    return true;
  todo(gateway_impl::QUERY MODULES RING 1);
  todo(gateway_impl::QUERY MODULES RING 2);
  todo(gateway_impl::QUERY MODULES RING 3);
}

void gateway_impl::PostNotify( const message &e )
{
  c.Notify(e);
}

bool gateway_impl::QueryModule( int global_id, const message &e )
{
  module *m = local_modules.GetModule(global_id);
  return m->Query(e);
}

#include "../messages/listen.h"

void gateway_impl::Listen( int source_instance, int dest_module, std::string module, std::string event )
{
  int module_global_id = RegisterName(MODULES, module);
  int event_global_id = RegisterName(EVENTS, event);
  Listen(source_instance, dest_module, module_global_id, event_global_id);
}

void gateway_impl::Listen( int source_instance, int dest_module, int module_global_id, int event_global_id )
{
  listen_message lm(event_global_id, module_global_id, source_instance);
  lm.listener_module = dest_module;

  c.Notify(static_cast<message>(lm));
  listeners.AddListener(lm, lm);
}

void gateway_impl::DelegateNotification( const message &mes )
{
  const event_notification en = mes;
  slot_data::event *e = listeners.GetEvent(en.source);
  if (!e)
    return; // no listeners registered;
  unsigned int i = 0, s = e->childs.size();
  for (i = 0; i < s; ++i)
  {
    module *m = local_modules.GetModule(e->childs[i].module);
    m->EventReciever(mes);
  }
}

void gateway_impl::IncomingNotification( message m )
{
  DelegateNotification(m);
  m.instance = reserved::instance::BROADCAST;
  DelegateNotification(m);
  m.module = reserved::module::BROADCAST;
  DelegateNotification(m);
}

void gateway_impl::Workflow()
{
  while (delayed_messages.size())
  {
    message m = delayed_messages.front();
    delayed_messages.pop_front();
    IncomingNotification(m);
  }
  if (c.Incoming() < 1)
    return;
  message *m = c.Get();
  if (!m)
    return;
  IncomingNotification(*m);
  delete m;
}