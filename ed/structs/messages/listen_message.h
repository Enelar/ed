#pragma once

#include "../message.h"

namespace messages
{
  struct listen_message
  {
    message_destination from;
    int what;

    listen_message() {}
    listen_message(raw_message &);

    operator vector<byte>();
  };

  typedef message<listen_message> listen;
}