#include "server_controller_impl.h"

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
  clients.AddListener(source, destination);
}


void server_controller_impl::MakeNotification( const message &a, const event_source &search_source )
{
  todo(Catch no event exception);
  slot::event &e = clients.GetEvent(search_source);
/*
  const slot_data::event::container_type &childs = e->childs;
  client_type &client = clients[a.instance];
  for (int i = 0, s = childs.size(); i < s; i++)
  {
    const listener &t = childs[i];
    client.Socket().Notify(a);
  }*/
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

  std::cout << "Registered name: " << r.nt << " " << r.name << " AS " << id << std::endl;
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
  MakeNotification(a, es);

  // broadcast listeners
  es.instance = reserved::instance::BROADCAST;
  MakeNotification(a, es);
  es.module = reserved::module::BROADCAST;
  MakeNotification(a, es);
}

void server_controller_impl::SysWorkflow( int i, connection &socket )
{
  const int min_message_length = 1;
  if (socket.Incoming() < min_message_length)
    return;

  message *m = NEW message(socket.Get());
  m->instance = i;
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
  NotifyWorkflow(i, socket, a);
}

void server_controller_impl::Workflow()
{
  if (ready.Ready())
  {
    connection *c = static_cast<connection *>(ready.Read());
    throw_assert(c);
    clients.AddInstance(c);
  }
  int i = 0, s = clients.data.size();

  for (; i < s; i++)
  {
    try
    {
      SysWorkflow(i, clients.GetInstance(i).Socket());
    } catch (slot_not_found &)
    {
    }
  }
}