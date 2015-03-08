#pragma once

#include "../message.h"

namespace messages
{
  struct translate_message
  {
    string name;

    translate_message(raw_message &);
  };

  typedef message<translate_message> translate;
}
