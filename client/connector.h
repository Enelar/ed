#pragma once

#include <ed/structs/message.h>
#include <ed/structs/library.h>

class connector
{
  int global_instance_id = ed::reserved::instance::BROADCAST;
  library names; // strings to global ids

public:
  void SendMessage(raw_message);
  raw_message WaitForMessage();

  int RegisterName(bool is_event, string name);

  friend class module;
};

extern connector singletone_connector;
