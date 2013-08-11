#include "gateway.h"
#include "../messages/register.h"
#include "../names/reserved.h"
#include "../3party/win/utils.h"

using namespace ed;
using namespace ed::com;


gateway::gateway( com::abstract_connection &_c )
  : impl(* NEW gateway_impl(*this, _c))
{
}

gateway::~gateway()
{
  delete &impl;
}

module &gateway::CreateModule( std::string name )
{
  return impl.CreateModule(name);
}

int gateway::RegisterName( NAME_TYPE nt, std::string name )
{
  return impl.RegisterName(nt, name);
}

void gateway::CreateModule( std::string name, module *const ret )
{
  impl.CreateModule(name, ret);
}


int gateway::RegisterEvent( std::string name )
{
  return impl.RegisterEvent(name);
}

bool gateway::PreNotify( const message &e )
{
  return impl.PreNotify(e);
}

void gateway::PostNotify( const message &e )
{
  impl.PostNotify(e);
}

bool gateway::QueryModule( int global_id, const message &e )
{
  return impl.QueryModule(global_id, e);
}

#include "../messages/listen.h"

void gateway::Listen( int source_instance, int dest_module, std::string module, std::string event )
{
  impl.Listen(source_instance, dest_module, module, event);
}

void gateway::Listen( int source_instance, int dest_module, int module_global_id, int event_global_id )
{
  impl.Listen(source_instance, dest_module, module_global_id, event_global_id);
}

void gateway::DelegateNotification( const message &mes )
{
  impl.DelegateNotification(mes);
}

void gateway::IncomingNotification( message m )
{
  impl.IncomingNotification(m);
}

void gateway::Workflow()
{
  impl.Workflow();
}