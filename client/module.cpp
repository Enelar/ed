#define _ED_INTERNAL_CONNECTOR_NOCHECK_
#include "module.h"
#include "connector.h"

module::module(string module_name)
{
  global_module_id = RegisterModuleName(module_name);
  singletone_connector.RegisterModule(global_module_id, this);
}

module::~module()
{
  singletone_connector.UnregisterModule(global_module_id);
}

void module::Emit(raw_message gift)
{
  gift.from.module = global_module_id;
  singletone_connector.Send(gift);
}

void module::Emit(int event, vector<byte> payload)
{
  Emit(event, ed::reserved::module::BROADCAST, payload);
}

void module::Emit(int event, int module, vector<byte> payload)
{
  Emit(event, module, ed::reserved::instance::BROADCAST, payload);
}

void module::Emit(int event, int module, int instance, vector<byte> payload)
{
  raw_message gift;
  gift.to.instance = instance;
  gift.to.module = module;
  gift.event = event;
  gift.payload = payload;
  Emit(gift);
}

int module::RegisterEventName(string name, int local_id)
{
  int global_id = singletone_connector.RegisterName(true, name);
  events.Insert(local_id, global_id);
  return global_id;
}

int module::RegisterModuleName(string name, int local_id)
{
  int global_id = singletone_connector.RegisterName(false, name);
  modules.Insert(local_id, global_id);
  return global_id;
}

string module::EventNameLookup(int local_id)
{
  int global_id = events.Local2Global(local_id);
  return singletone_connector.names.events.Local2Global(global_id);
}

string module::ModuleNameLookup(int local_id)
{
  int global_id = modules.Local2Global(local_id);
  return singletone_connector.names.modules.Local2Global(global_id);
}

void module::Listen(int event, int module, int instance)
{
  singletone_connector.Listen(event, global_module_id, { instance, module });
}

void module::OnMessage(raw_message origin)
{
  if (origin.to.module >= ed::reserved::module::FIRST_ALLOWED)
    if (origin.to.module != global_module_id)
      throw "wow. some connector issue";
    else
      origin.to.module = modules.Global2Local(origin.to.module);
  
  if (origin.event >= ed::reserved::event::FIRST_ALLOWED)
    origin.event = events.Global2Local(origin.event);

  handler_stored handler;
  try
  {
    handler = callbacks.Global2Local(origin.event);
  }
  catch (vocabulary_exceptions::unknown &)
  { // Hm. Another weird connector issue
    throw "wow. module not declared handler for this event.";
  }
  
  (*handler)(origin);
}