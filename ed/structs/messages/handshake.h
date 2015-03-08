#pragma once

#include "../message.h"

namespace messages
{
  struct handshake_message
  {
    int version = ed::reserved::protocol_version;

    handshake_message() {};
    handshake_message(raw_message &);

    operator vector<byte>();
  };

  struct handshake : message<handshake_message>
  {
    handshake();
    handshake(raw_message &);

    operator vector<byte>();
  };
}