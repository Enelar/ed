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
  if (size > that.payload.size() - 4)
    throw "string too big";
  copy((char *)buf, (char *)buf + 4 + size, str.begin());
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
  auto *buf = &that.payload[0];
  num = *(int *)buf;
}

int_message::operator vector<byte>()
{
  vector<byte> ret;
  ret.push_back(num);
  return ret;
}