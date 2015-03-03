#pragma once

#include "module.h"

template<typename T, typename MODULE>
auto module::Listen(
  void (MODULE::*cb)(T),
  int event,
  int module,
  int instance
  ) -> void
{
  typedef handle_adapter<MODULE, T> my_adapter;
  //my_adapter test((MODULE &)*this, cb);
  shared_ptr<my_adapter> adapter = make_shared<my_adapter>((MODULE &)*this, cb);
  callbacks.Insert(event, adapter);
}
