/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

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
void _TEMPLATE_::MakeNotification( event_notification e )
{
  slot_data::event &e = GetEvent(e.source);
  todo(Send notifications);
}

template<class ready_type>
void _TEMPLATE_::Workflow()
{
  if (ready->Ready())
  {
    connection *c = ready->Read();
    throw_assert(c);
    todo("Slot by connection");
  }
  int i = 0, s = clients.size();

  for (; i < s; i++)
  {
    const int min_message_length = 1;
    if (Incoming() >= min_message_length)
    {
      todo("Read message");
      todo("If message notification. Could be register and add listener");
      event_notification e;
      todo("Fill event_notification");
      MakeNotification(e);
    }
  }
}

#undef _TEMPLATE_