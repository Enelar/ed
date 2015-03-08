#include "listen_message.h"

using namespace messages;

listen_message::listen_message(raw_message &that)
{
  auto *p = &that.payload[0];
  what = *p++;
  from.instance = *p++;
  from.module = *p++;
}

listen_message::operator vector<byte>()
{
  vector<byte> ret;
  ret.push_back(what);
  ret.push_back(from.instance);
  ret.push_back(from.module);
  return ret;
}