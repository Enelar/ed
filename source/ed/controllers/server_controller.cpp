/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_SERVER_CONTROLLER_H_
#include "server_controller.h"
#else

#define _ED_SERVER_CONTROLLER_IMPL_
#define _TEMPLATE_ server_controller<connection>

template<class connection>
typename _TEMPLATE_::id_type _TEMPLATE_::RegisterName( NAME_TYPE nt, word_type name )
{
  return names[nt].RegisterWord(name);
}

#undef _TEMPLATE_

#endif