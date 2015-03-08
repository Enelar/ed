#pragma once

#include "module.h"

// Step Three: Store and tell connector
template<typename T, typename MODULE>
void module::Listen(void (MODULE::*cb)(T),
  ed::translator_hook_event event,
  ed::translator_hook_module module,
  ed::translator_hook_instance instance)
{
  if (event.is_local)
  {
    event = events.Local2Global(event.local_id);
    event.is_local = false;
  }

  if (module.is_local)
  {
    module = modules.Local2Global(event.local_id);
    module.is_local = false;
  }

  typedef handle_adapter<MODULE, T> my_adapter;

  shared_ptr<my_adapter> adapter = make_shared<my_adapter>((MODULE &)*this, cb);
  callbacks.Insert(adapter, event);

  Listen(event, module, instance);
}