#include "server_controller_impl.h"
#include <algorithm>

using namespace ed;

server_controller_impl::server_controller_impl( ready_type &_ready )
  :
  ready(_ready)
{

}


server_controller_impl::~server_controller_impl( )
{
}


server_controller_impl::id_type server_controller_impl::RegisterName( NAME_TYPE nt, word_type name )
{
  return names[nt].RegisterWord(name);
}


void server_controller_impl::AddListener( event_source source, listener destination )
{
  clients.AddListener(source, destination, true);
}

void server_controller_impl::MakeNotification( int i, const message &a )
{
  slot::instance &inst = clients.GetInstance(i);
  if (!inst.con)
    return;
  com::abstract_connection &con = inst.Socket();
  con.Notify(a);
  std::cout << "[" << i << "] NOTIFIED ABOUT " <<
    a.event << " EVENT " << std::endl;
}

void server_controller_impl::RegisterWorkflow( int i, connection &socket, const register_message &r )
{
  id_type id = RegisterName(r.nt, r.name);
  event_notification e(4); // 32 bit
  e.source.instance = i;
  e.source.module = 0;
  e.source.event = ed::reserved::event::EVENT_REGISTER;
  memcpy(e.payload, &id, 4);
  socket.Notify(e);

  char 
   *debug = "  name";
  if (r.nt == MODULES)
    debug = "module";
  if (r.nt == EVENTS)
    debug = " event";
  std::cout << "Registered " << debug << ": " << r.name << " AS " << id << std::endl;
}

void server_controller_impl::ListenWorkflow( int i, connection &socket, const listen_message &res )
{
  listen_message lm = res;
  lm.listener_instance = i;
  AddListener(lm, lm);
  std::cout << lm.listener_instance << ":" << (int)lm.listener_module << " LISTEN " << lm.event << " FROM " <<
    lm.event_source_instance << ":" << (int)lm.event_source_module << std::endl;
}

void server_controller_impl::NotifyWorkflow( int i, connection &socket, const message &a )
{
  if (a.flags.ring < RING2_NETWORK)
    return;
  if (a.flags.state == PRE_REPLY)
    todo(PRE REPLY ON SERVER CONTROLLER);
  std::cout << "EVENT " << a.event << " APPEARS FROM " << a.instance << ":" << (int)a.module << std::endl;
  event_source es = static_cast<event_notification>(a);

  if (a.flags.exclusive)
    throw_message("Todo exclusive send");

  std::set<int> instances = clients.Subscribed(&slot_data::listener::instance, es);
  std::set<int>::const_iterator it = instances.begin(), e = instances.end();
  while (it != e)
  {
    if (*it != i)
      MakeNotification(*it, a);
    it++;
  }
}

void server_controller_impl::SysWorkflow( int i, connection &socket )
{
  const int min_message_length = 1;
  if (socket.Incoming() < min_message_length)
    return;
  message *m = NEW message(socket.Get());
  decltype(m->instance) instance = i;
  std::swap(instance, m->instance);
  if (!m)
    return;

  if (m->event == reserved::event::EVENT_GLOBAL_ID_REQUEST ||
    m->event == reserved::event::MODULE_GLOBAL_ID_REQUEST)
  {
    register_message r = *m;
    delete m;
    RegisterWorkflow(i, socket, r);
    return;
  }

  if (m->event == reserved::event::LISTEN)
  {
    listen_message lm = *m;
    delete m;
    ListenWorkflow(i, socket, lm);
    return;
  }
  message a = *m;
  delete m;
  std::swap(instance, a.instance);
  // because on notify message(client recieve) instance should contain target
  NotifyWorkflow(i, socket, a);
}

#include "../exceptions/disconnected.h"

void server_controller_impl::Workflow()
{
  if (ready.Ready())
  {
    connection *c = static_cast<connection *>(ready.Read());
    throw_assert(c);
    std::cout << "New ED instance! ID: " << clients.AddInstance(c) << std::endl;
    
  }
  int i = 0, s = clients.data.size();

  for (; i < s; i++)
  {
    try
    {
      slot::instance &inst = clients.GetInstance(i);
      if (!inst.con)
        continue;
      SysWorkflow(i, inst.Socket());
    } catch (slot_not_found &)
    {
      std::cout << "Slot not found exception catched" << std::endl;
    } catch (ed::disconnected &)
    {
      std::cout << "ED instance " << i << " disconnected" << std::endl;
      clients.RemoveDisconnected(i);
    }
  }
}
