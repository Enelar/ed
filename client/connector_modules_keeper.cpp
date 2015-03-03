#define _ED_INTERNAL_CONNECTOR_NOCHECK_
#include "connector.h"
#include <ed/structs/messages/simple_messages.h>

void connector::RegisterModule(int global_module_id, module *that)
{
  modules.insert({global_module_id, that});

  messages::_void gift;
  gift.event = ed::reserved::event::MODULE_UP;
  gift.to.instance = ed::reserved::instance::BROADCAST;
  gift.to.module = ed::reserved::module::HEART_BEAT;
  gift.from.instance = global_instance_id;
  gift.from.module = global_module_id;

  Send(gift);
}

void connector::UnregisterModule(int global_module_id)
{
  messages::_void gift;
  gift.event = ed::reserved::event::MODULE_DOWN;
  gift.to.instance = ed::reserved::instance::BROADCAST;
  gift.to.module = ed::reserved::module::HEART_BEAT;
  gift.from.instance = global_instance_id;
  gift.from.module = global_module_id;

  Send(gift);

  modules.erase(global_module_id);

  for (auto &event_row : listeners)
  {
    auto &listen_modules = event_row.second;
    auto &it = listen_modules.find(global_module_id);
    if (it == listen_modules.end())
      continue;
    listen_modules.erase(it);
  }
}
