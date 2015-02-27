#include "message.h"

message_header::message_header()
{
}

message_header::message_header(byte *arr)
{
  int *p = reinterpret_cast<int *>(arr);
  event = *p++;
  to.instance = *p++;
  to.module = *p++;
  from.instance = *p++;
  from.module = *p++;
}

message_header::operator vector<byte>() const
{
  vector<byte> ret;
  ret.push_back(event);
  ret.push_back(to.instance);
  ret.push_back(to.module);
  ret.push_back(from.instance);
  ret.push_back(from.module);

  return ret;
}

raw_message::raw_message()
{
}

raw_message::raw_message(byte *arr)
  : message_header(arr)
{
  arr += message_header::raw_byte_size;
  int size = *reinterpret_cast<int *>(arr);
  arr += 4;

  if (size > max_message_size)
    throw "Max message size";

  for (auto i = 0; i < size; i++)
    payload.push_back(arr[i]);
}

raw_message::operator vector<byte>() const
{
  vector<byte> ret = *(message_header *)this;
  ret.push_back(payload.size());

  for (auto b : payload)
    ret.push_back(b);

  return ret;
}