#define _ED_SERVER_CONTROLLER_IMPL_
#ifndef _ED_SERVER_CONTROLLER_H_
#include "server_controller.h"
#endif

#define _TEMPLATE_ server_controller<ready_type>

template<class ready_type>
_TEMPLATE_::server_controller( ready_type *_ready ) : ready(_ready)
{
  throw_assert(_ready);
}

template<class ready_type>
_TEMPLATE_::~server_controller( )
{
  delete ready;
}

template<class ready_type>
typename _TEMPLATE_::id_type _TEMPLATE_::RegisterName( NAME_TYPE nt, word_type name )
{
  return names[nt].RegisterWord(name);
}

template<class ready_type>
void _TEMPLATE_::AddListener( event_source source, listener destination )
{
  //! @NOTE Not really good, maybe all childs should be in common container??
  int target = source.instance;
  throw_assert(target >= 0);
  throw_assert(target < childs.size());
  childs[target].AddListener(source, destination);
}

template<class ready_type>
void _TEMPLATE_::MakeNotification( event_notification a )
{ //! @NOTE Crap code again
  slot_data::event &e = clients[a.source.instance].GetEvent(a.source);
  todo(Send notifications);
}

template<class ready_type>
void _TEMPLATE_::Workflow()
{
  if (ready->Ready())
  {
    connection *c = static_cast<connection *>(ready->Read());
    throw_assert(c);
    clients.push_back(client_type(c));
  }
  int i = 0, s = clients.size();

  for (; i < s; i++)
  {
    const int min_message_length = 1;
    connection &socket = clients[i].Socket();
    if (socket.Incoming() >= min_message_length)
    {
      message *m = socket.Get();
      if (!m)
        continue;
      if (m->event != reserved::event::EVENT_GLOBAL_ID_REQUEST &&
        m->event != reserved::event::MODULE_GLOBAL_ID_REQUEST)
        todo("Read message");
      register_message r = *m;
      delete m;
      id_type id = RegisterName(r.nt, r.name);
      event_notification e(4); // 32 bit
      e.source.instance = i;
      e.source.module = 0;
      e.source.event = ed::reserved::event::EVENT_REGISTER;
      memcpy(e.payload, &id, 4);
      socket.Notify(e);
    }
  }
}

#undef _TEMPLATE_