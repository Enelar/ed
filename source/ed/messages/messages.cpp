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

message::message( int payload_size )
{
  throw_assert(payload_size >= 0);
  
  flags.ring = 0;
  flags.size_length = 0;
  flags.state = 0;
  dest = 0;
  size = 0;
  event = 0;
  module = 0;
  instance = 0;
  if (payload_size)
    payload = NEW buffer(payload_size);
  else
    payload = NULL;
}

message::message( const message &m )
{
  *this = m;
}

message &message::operator=( const message &m )
{
  if (this == &m)
    return *this;
  flags = m.flags;
  dest = m.dest;
  event = m.event;
  module = m.module;
  instance = m.instance;
  if (m.payload)
    payload = NEW buffer(*m.payload);
  else
    payload = NULL;
}

message::operator buffer() const
{
  todo(Message to buffer);
  throw_assert(Completed());
  int length = SizeLength();
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

#include "../exceptions/exception.h"

int message::SizeLength() const
{
  int length = 0;
  if (payload)
    length += payload->len;
  length += message::MinRequiredSize();
  length += 1; // for size
  if (length < (1 << 8))
    return 1;
  length += 1; // for size
  if (length < (1 << 16))
    return 2;
  throw_message("Very big message!!!");
}