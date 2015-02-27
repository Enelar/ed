#pragma once

#include <vector>
typedef unsigned char byte;

using namespace std;

#include "constants.h"

struct message_header
{
  struct
  {
    int instance, module;
  } to;
  struct
  {
    int instance, module;
  } from;

  int event;

  message_header();
  message_header(byte *);

  operator vector<byte>() const;

  static const int raw_byte_size = 5 * 4;
};

struct raw_message : message_header
{
  vector<byte> payload;

  static const int max_message_size = 1 << 14;

  raw_message();
  raw_message(byte *);

  operator vector<byte>() const;
};

template<typename T>
struct message : message_header
{
  T payload;

  operator vector<byte>() const
  {
    vector<byte> ret = *(message_header *)this;
    vector<byte> res = payload;
    ret.insert(ret.end(), res.begin(), res.end());
    return ret;
  }
};
