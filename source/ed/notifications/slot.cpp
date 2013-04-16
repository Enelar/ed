/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#define _ED_NOTIFICATIONS_SLOT_IMPL_
#ifndef _ED_NOTIFICATIONS_SLOT_H_
#include "slot.h"
#endif

#define _TEMPLATE_ slot<connection>

template<typename connection>
_TEMPLATE_::slot( connection *_socket )
  : socket(_socket)
{
  throw_assert(socket);
}

template<typename connection>
connection &_TEMPLATE_::Socket() const
{
  return *socket;
}

template<typename connection>
_TEMPLATE_::~slot()
{
  delete socket;
}


#undef _TEMPLATE_