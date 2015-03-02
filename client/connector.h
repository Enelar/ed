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
};

extern connector sigletone_connector;
