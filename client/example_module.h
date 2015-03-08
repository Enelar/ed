#pragma once

#include "module.h"

struct example_module : protected module
{
  example_module();

  void Subscribe();
  void Emit();

  void ExampleHandler(raw_message);
};
