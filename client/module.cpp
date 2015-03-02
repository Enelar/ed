#include "module.h"
#include "connector.h"

module::module(string module_name)
{
  global_module_id = RegisterModuleName(module_name);
}

void module::Emit(raw_message gift)
{
  gift.from.module = global_module_id;
  sigletone_connector.SendMessage(gift);
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