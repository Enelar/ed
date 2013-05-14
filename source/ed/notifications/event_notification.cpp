#include "event_notification.h"

using namespace ed;

event_notification::operator message() const
{
  throw_assert(payload_size < 256 && payload_size >= 0);
  message ret(payload_size);
  ret.dest = target_module;
  ret.event = source.event;
  ret.module = source.module;
  ret.instance = source.instance;
  if (payload_size)
    memcpy(ret.payload->buf, payload, payload_size);
  return ret;
}

event_notification::event_notification( const message &m )
  : payload_size(m.PayloadSize()),
    payload(NULL)
{
  if (payload_size)
  {
    payload = NEW char[payload_size];
    memcpy(payload, m.payload->buf, payload_size);
  }
  target_module = m.dest;
  source.event = m.event;
  source.module = m.module;
  source.instance = m.instance;
}