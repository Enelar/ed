#include "module.h"
#include "connector.h"

module::module(string module_name)
{
  global_module_id = RegisterModuleName(module_name);
}

void module::Emit(raw_message gift)
{
  gift.from.module = global_module_id;
  singletone_connector.SendMessage(gift);
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