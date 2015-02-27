#include "simple_messages.h"

messages::string_message::string_message(raw_message &that)
{
  auto *buf = &that.payload[0];
  copy((char *)buf, (char *)buf + that.payload.size(), str.begin());
}

messages::int_message::int_message(raw_message &that)
{
  auto *buf = &that.payload[0];
  num = *(int *)buf;
}

messages::int_message::operator vector<byte>()
{
  vector<byte> ret;
  ret.push_back(num);
  return ret;
}