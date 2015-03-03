#pragma once

#include "module.h"

struct example_module : public module
{
  example_module();
  
  void Subscribe();
  void Emit();

  raw_message WaitForMessage();

  void ExampleHandler(raw_message);


};
