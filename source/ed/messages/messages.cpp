#include "message.h"

using namespace ed;

message::message( const buffer &a )
  : payload(NULL)
{
  throw_assert(a.len > 0);
  flags = *reinterpret_cast<flag_byte *>(a.buf);
  todo(CheckConversation);
  throw_assert(a.len >= ExpectedSize(flags));
  dest = a.buf[1];
  int offset = OffsetToEventSegment();
  event = *(word *)(a.buf + offset);
  module = a.buf[offset + 2];
  instance = *(word *)(a.buf + offset + 3);
  if (a.len >= MessageSize())
  {
    payload = NEW buffer(size);
    memcpy(payload->buf, a.buf + offset + 5, size);
  }
}

message::operator buffer() const
{
  todo(Message to buffer);
  throw_assert(Completed());
  int length = 0;
  if (payload)
  {
    if (payload->len > 0)
      if (payload->len >= (1 << 8))
      {
        throw_assert(payload->len < (1 << 16));
        length = 2;
      }
      else
        length = 1;
  }
  flags.size_length = length;
  buffer ret(MessageSize());
}

message::~message()
{
  if (payload)
    delete payload;
}

int message::OffsetToEventSegment()
{
  return sizeof(flag_byte) + sizeof(byte) + size;
}

int message::MessageSize() const
{
  return ExpectedSize(flags) + PayloadSize();
}

bool message::Completed() const
{
  if (payload)
    return (size - ExpectedSize(flags)) == payload->len;
  return size == ExpectedSize(flags);
}