#include "register.h"
#include "../names/reserved.h"

using namespace ed;

register_message::operator message() const
{
  message ret(name.length());
  memcpy(ret.payload->buf, name.c_str(), ret.payload->len);
  switch (nt)
  {
  case MODULES:
    ret.event = reserved::event::MODULE_GLOBAL_ID_REQUEST;
    break;
  case EVENTS:
    ret.event = reserved::event::EVENT_GLOBAL_ID_REQUEST;
    break;
  default:
    dead_space();
  };
  ret.module = reserved::module::BROADCAST;
  ret.instance = reserved::instance::BROADCAST;
  ret.dest = reserved::module::BROADCAST;
  return ret;
}