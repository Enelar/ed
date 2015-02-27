#pragma once

#include <vector>
typedef unsigned char byte;

using namespace std;

#include "constants.h"

struct message_payload
{
  vector<byte> message;
};

struct message_header
{
  struct
  {
    int instance, module, event;
  } from;
  struct
  {
    int instance, module;
  } to;
};

struct raw_message : message_header
{
  message_payload payload;
};

template<typename T>
struct message : message_header
{
  T payload;
};
