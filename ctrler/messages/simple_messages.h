#pragma once

#include "../message.h"

namespace messages
{
  struct string_message
  {
    string str;

    string_message() {}
    string_message(raw_message &);

    operator vector<byte>();
  };

  typedef message<string_message> _string;

  struct int_message
  {
    int num;

    int_message() {}
    int_message(raw_message &);

    operator vector<byte>();
  };

  typedef message<int_message> _int;
}
