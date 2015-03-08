#pragma once

#include "module.h"

// Step One: Translate local module ID to global
template<typename T, typename MODULE, typename eventT>
void module::Listen(void (MODULE::*cb)(T), eventT event, int local_module_id, int instance)
{
  const auto module = (ed::reserved::module::MODULE) modules.Local2Global(local_module_id);
  Listen(cb, event, module, instance);
}

// Step Two: Translate local event ID to global
template<typename T, typename MODULE>
void module::Listen(void (MODULE::*cb)(T), 
   int local_event_id, 
   ed::reserved::module::MODULE module, int instance)
{
  const auto event = (ed::reserved::event::EVENT)events.Local2Global(local_event_id);
  Listen(cb, event, module, instance);
}

// Step Three: Store and tell connector
template<typename T, typename MODULE>
void module::Listen(void (MODULE::*cb)(T),
  ed::reserved::event::EVENT event,
  ed::reserved::module::MODULE module,
  int instance)
{
  typedef handle_adapter<MODULE, T> my_adapter;

  shared_ptr<my_adapter> adapter = make_shared<my_adapter>((MODULE &)*this, cb);
  callbacks.Insert(adapter, event);

  Listen(event, module, instance);
}