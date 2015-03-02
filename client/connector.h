#pragma once

#include <ed/structs/message.h>
#include <ed/structs/library.h>
#include <ed/structs/message.h>

class connector
{
  int instance_id = 0;
  library names; // strings to global ids

public:
  void SendMessage(const raw_message &);
  raw_message WaitForMessage();

  int RegisterName(bool is_event, string name);

  friend class module;
};

extern connector singletone_connector;
