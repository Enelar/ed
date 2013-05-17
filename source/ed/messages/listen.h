#ifndef _ED_MESSAGES_LISTEN_H_
#define _ED_MESSAGES_LISTEN_H_

#include "message.h"

namespace ed
{
  struct listen_message
  {
    typedef message::word word;
    typedef message::byte byte;

    word event;
    word event_source_instance;
    byte event_source_module;

    word listener_module;
    word listener_instance;

    listen_message( word _event, byte _event_source_module, word _event_source_instance )
      : event(_event), event_source_instance(_event_source_instance), event_source_module(_event_source_module),
      listener_instance(reserved::instance::BROADCAST), listener_module(reserved::module::BROADCAST)
    {
      
    }

    listen_message( message &e )
    {
      throw_assert(e.PayloadSize() == 5);
      const byte *buffer = e.payload->buf;
      event = *(word *)(buffer);
      event_source_instance = *(word *)(buffer + 1);
      event_source_module = buffer[3];
    }

    operator message() const
    {
      message ret(5);
      byte *buffer = ret.payload->buf;
      *(word *)(buffer) = event;
      *(word *)(buffer + 1) = event_source_instance;
      buffer[3] = event_source_module;

      ret.event = reserved::event::LISTEN;
      return ret;
    }
  };
};

#endif