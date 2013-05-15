#include "gateway.h"
#include "../messages/register.h"
#include "../names/reserved.h"
#include "../3party/win/utils.h"

using namespace ed;
using namespace ed::com;

namespace
{
  struct register_answer
  {
    int global_id;
    int instance_id;
  };
  register_answer RegisterName( abstract_connection &c, NAME_TYPE nt, std::string name )
  {
    register_message rm(nt, name);
    c.SendRegister(rm);

    while (c.Incoming() < 1)
      ed::Sleep(1);
    message *m = c.Get();
    throw_assert(m);
    throw_assert(m->event == reserved::event::EVENT_REGISTER);
    event_notification e = *m;
    delete m;
    throw_assert(e.source.event == reserved::event::EVENT_REGISTER);
    throw_assert(e.payload_size == 4);
    register_answer ret;
    ret.global_id = *(int *)e.payload;
    ret.instance_id = e.source.instance;
    return ret;
  }
};

gateway::gateway( com::abstract_connection &_c )
  : c(_c)
{
}

module &gateway::CreateModule( std::string name )
{
  return *NEW module(name, *this);
}

void gateway::CreateModule( std::string name, module *const ret )
{
  register_answer answer = RegisterName(c, MODULES, name);
  instance = answer.instance_id;
  int id = answer.global_id;
  ret->id = id;
  local_modules.AddModule(ret, id);
}


int gateway::RegisterEvent( std::string name )
{
  register_answer answer = RegisterName(c, EVENTS, name);
  instance = answer.instance_id;
  int id = answer.global_id;
  return id;
}

bool gateway::PreNotify( const message &e )
{
  if (e.flags.ring == 0)
    return true;
  todo(gateway::QUERY MODULES RING 1);
  todo(gateway::QUERY MODULES RING 2);
  todo(gateway::QUERY MODULES RING 3);
}

void gateway::PostNotify( const message &e )
{
  c.Notify(e);
}

bool gateway::QueryModule( int global_id, const message &e )
{
  module *m = local_modules.GetModule(global_id);
  return m->Query(e);
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