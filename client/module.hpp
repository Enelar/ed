#pragma once

#include "module.h"

// Step One: Translate local module ID to global
template<typename T, typename MODULE, typename eventT>
void module::Listen(void (MODULE::*cb)(T), eventT event, int module, int instance)
{
  module = modules.Local2Global(module);
  Listen(cb, event, (ed::reserved::module::MODULE)module, instance);
}

// Step Two: Translate local event ID to global
template<typename T, typename MODULE>
void module::Listen(void (MODULE::*cb)(T), 
   int event, 
   ed::reserved::module::MODULE module, int instance)
{
  event = events.Local2Global(event);
  Listen(cb, (ed::reserved::event::EVENT)event, module, instance);
}

// Step Three: Store and tell connector
template<typename T, typename MODULE>
void module::Listen(void (MODULE::*cb)(T),
  ed::reserved::event::EVENT event,
  ed::reserved::module::MODULE module, int instance)
{
  typedef handle_adapter<MODULE, T> my_adapter;

  shared_ptr<my_adapter> adapter = make_shared<my_adapter>((MODULE &)*this, cb);
  callbacks.Insert(adapter, event);
  Listen(event, module, instance);
}