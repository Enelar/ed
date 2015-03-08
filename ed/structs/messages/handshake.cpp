#include "handshake.h"

using namespace messages;

handshake_message::handshake_message(raw_message &raw)
{
  if (raw.payload.size() < 4)
    throw "handshake issue";
  version = *(int *)&raw.payload[0];
}

handshake_message::operator vector<byte>()
{
  return{ (char *)&version, (char *)&version + 4 };
}

handshake::handshake()
{
  event = ed::reserved::event::INSTANCE_UP;
  to.instance = ed::reserved::instance::BROADCAST;
  to.module = ed::reserved::module::HEART_BEAT;
  from.instance = ed::reserved::instance::BROADCAST;
  from.module = ed::reserved::module::HEART_BEAT;
}

handshake::handshake(raw_message &raw)
  : message(raw)
{
}

handshake::operator vector<byte>()
{
  vector<byte> ret = *((message_header*)this);
  vector<byte> raw_payload = payload;
  ret.insert(ret.end(), raw_payload.begin(), raw_payload.end());
  return ret;
}