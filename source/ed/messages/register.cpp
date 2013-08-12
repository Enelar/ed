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

register_message::register_message( message &e )
  : name(*NEW std::string())
{
  switch (e.event)
  {
  case reserved::event::EVENT_GLOBAL_ID_REQUEST:
    nt = EVENTS;
    break;
  case reserved::event::MODULE_GLOBAL_ID_REQUEST:
    nt = MODULES;
    break;
  default:
    dead_space();
  }
  char *temp = NEW char[e.payload->len + 1];
  memcpy(temp, e.payload->buf, e.payload->len);
  temp[e.payload->len] = 0;
  name = temp;
  delete []temp;
}