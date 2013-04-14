/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#define _ED_SERVER_CONTROLLER_IMPL_
#ifndef _ED_SERVER_CONTROLLER_H_
#include "server_controller.h"
#endif

#define _TEMPLATE_ server_controller<connection_ready>

template<class connection_ready>
_TEMPLATE_::server_controller( connection_ready *_ready ) : ready(_ready)
{
  throw_assert(_ready);
}

template<class connection_ready>
typename _TEMPLATE_::id_type _TEMPLATE_::RegisterName( NAME_TYPE nt, word_type name )
{
  return names[nt].RegisterWord(name);
}

template<class connection_ready>
void _TEMPLATE_::AddListener( event_source source, listener destination )
{
  //! @NOTE Not really good, maybe all childs should be in common container??
  int target = source.instance;
  throw_assert(target >= 0);
  throw_assert(target < childs.size());
  childs[target].AddListener(source, destination);
}

template<class connection_ready>
void _TEMPLATE_::MakeNotification( event_notification e )
{
  slot_data::event &e = GetEvent(e.source);
  todo(Send notifications);
}

template<class connection_ready>
void _TEMPLATE_::Workflow()
{
  todo(Workflow);
}

#undef _TEMPLATE_