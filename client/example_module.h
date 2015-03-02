#pragma once

#include "module.h"

class example_module : public module
{
  example_module();
  
  void Subscribe();
  void Emit();

  raw_message WaitForMessage();


};
