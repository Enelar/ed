#pragma once

#include "module.h"

template<typename T>
auto module::Listen(
  void (module::*cb)(message<T>),
  int event,
  int module,
  int instance
  ) -> void
{
  Listen((event_handler)cb, event, module, instance);
}
