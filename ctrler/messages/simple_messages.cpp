#include "simple_messages.h"

using namespace messages;

void_message::void_message(raw_message &)
{

}

void_message::operator vector<byte>()
{
  return{};
}


string_message::string_message(raw_message &that)
{
  auto *buf = &that.payload[0];
  copy((char *)buf, (char *)buf + that.payload.size(), str.begin());
}

int_message::int_message(raw_message &that)
{
  auto *buf = &that.payload[0];
  num = *(int *)buf;
}

int_message::operator vector<byte>()
{
  vector<byte> ret;
  ret.push_back(num);
  return ret;
}