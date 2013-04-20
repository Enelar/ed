/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#include "gateway.h"
#include "../messages/register.h"
#include "../3party/win/utils.h"

using namespace ed;
using namespace ed::com;

namespace
{
  int RegisterName( abstract_connection &c, NAME_TYPE nt, std::string name )
  {
    register_message rm(MODULES, name);
    c.SendRegister(rm);

    todo(Register name at client);
    while (c.Incoming() < 10)
      ed::Sleep(1);
    //c.Read
  }
};

gateway::gateway( com::abstract_connection &_c )
  : c(_c)
{
}

module &gateway::CreateModule( std::string name )
{
  int id = RegisterName(c, MODULES, name);
  module *ret = NEW module(id, *this);
  return *ret;
}

int gateway::RegisterEvent( std::string name )
{
  int id = RegisterName(c, EVENTS, name);
  return id;
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