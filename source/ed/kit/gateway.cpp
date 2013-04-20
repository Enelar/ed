/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#include "gateway.h"

using namespace ed;
using namespace ed::com;

gateway::gateway( com::abstract_connection &_c )
  : c(_c)
{
}

module &gateway::CreateModule( std::string name )
{
  module *ret = NEW module(*this);
  return *ret;
}


#if 0
#define _ED_KIT_GATEWAY_IMPL_
#ifndef _ED_KIT_GATEWAY_H_
#include "gateway.h"
#endif

#define _TEMPLATE_ gateway<connection>

template<typename connection>
module &_TEMPLATE_::CreateModule( std::string name )
{
  module *ret = new module();
  return *ret;
}

#undef _TEMPLATE_

#endif