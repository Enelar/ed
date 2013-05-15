#include "message.h"

using namespace ed;

message::message( const buffer &a )
  : payload(NULL)
{
  throw_assert(a.len > 0);
  flag_byte fb = *reinterpret_cast<flag_byte *>(a.buf);
  flags = fb;

  throw_assert(a.len >= ExpectedSize(flags));
  dest = a.buf[1];
  if (flags.size_length == 1)
    size = a.buf[2];
  else
    size = *(word *)(a.buf + 2);
  int offset = OffsetToEventSegment();
  event = *(word *)(a.buf + offset);
  module = a.buf[offset + 2];
  instance = *(word *)(a.buf + offset + 3);
  if (a.len >= ExpectedSize(flags) + ExpectedPayloadSize())
  {
    payload = NEW buffer(size);
    memcpy(payload->buf, a.buf + offset + 5, size);
  }
}

message::operator buffer() const
{
  int length = SizeLength();
  flags.size_length = length;
  size = ExpectedSize(flags) + PayloadSize();
  throw_assert(Completed());
  buffer ret(MessageSize());
  flag_byte fb = flags;
  memcpy(ret.buf, &fb, 1);
  ret.buf[1] = dest;
  throw_assert(flags.size_length && flags.size_length != 3);
  if (flags.size_length == 1)
    ret.buf[2] = (byte)size;
  else
    *(word *)(ret.buf + 2) = size;
  int offset = OffsetToEventSegment();
  *(word *)(ret.buf + offset) = event;
  ret.buf[offset + 2] = module;
  *(word *)(ret.buf + offset + 3) = instance;
  memcpy(ret.buf + offset + 5, payload->buf, payload->len);
  return ret;
}

message::message( int payload_size )
{
  throw_assert(payload_size >= 0);
  
  flags.ring = RING3_WORLD;
  flags.size_length = 0;
  flags.state = POST_COMMIT;
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
  return *this;
}

message::~message()
{
  if (payload)
    delete payload;
}

int message::OffsetToEventSegment() const
{
  return sizeof(byte) + sizeof(byte) + SizeLength();
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

int message::ExpectedPayloadSize() const
{
  return size - ExpectedSize(flags);
}