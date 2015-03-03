#pragma once

#include <vector>
typedef unsigned char byte;

using namespace std;

#include "constants.h"

struct message_destination
{
  int instance, module;
};

struct message_header
{
  message_destination to;
  message_destination from;

  int event;

  void Reverse();
  void Fill(const message_header &);

  message_header();
  message_header(byte *);

  operator vector<byte>() const;

  static const int raw_byte_size = 5 * 4;
};

template<typename T> struct message;
struct raw_message : message_header
{
  vector<byte> payload;

  static const int max_message_size = 1 << 14;

  raw_message();
  raw_message(byte *);

  operator vector<byte>() const;

  template<typename T>
  raw_message(message<T> &that);
};

template<typename T>
struct message : message_header
{
  T payload;

  message() {}

  operator vector<byte>() const
  {
    vector<byte> ret = *(message_header *)this;
    vector<byte> res = payload;
    ret.insert(ret.end(), res.begin(), res.end());
    return ret;
  }

  message(raw_message &that)
    : message_header(that), payload(that)
  {
  }
};

template<typename T>
raw_message::raw_message(message<T> &that)
: message_header(that), payload(that.payload)
{}

