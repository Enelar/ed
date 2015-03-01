#pragma once

#include <ed/structs/library.h>
#include <ed/structs/message.h>

class example_module
{
  library names;

  int GetNameID(bool is_event, string name);
  void Send(const raw_message &);

  void Subscribe();
  void Emit();

  raw_message WaitForMessage();


};
