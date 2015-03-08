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
{ // BUG: UTF strings, not ASCII !!!
  auto *buf = &that.payload[0];
  int size = *reinterpret_cast<int *>(buf);

  const auto sizeof_size = 4;
  buf += sizeof_size;

  if (size > that.payload.size() - sizeof_size)
    throw "string too big";

  str.resize(size);
  copy((char *)buf, (char *)buf + size, str.begin());
}

string_message::operator vector<byte>()
{ // BUG: UTF strings, not ASCII !!!
  int size = str.size();
  char *bytes = &str[0];
  vector<byte> ret;
  ret.resize(size + 4);
  *(int *)&ret[0] = size;

  for (auto i = 0; i < size; i++)
    ret[i + 4] = str[i];

  return ret;
}

int_message::int_message(raw_message &that)
{
  if (that.payload.size() < 4)
    throw "int payload should be at least 4 bytes long";
  auto *buf = &that.payload[0];
  num = *(int *)buf;
}

int_message::operator vector<byte>()
{
  vector<byte> ret(4);
  *(int *)&ret[0] = num;
  return ret;
}