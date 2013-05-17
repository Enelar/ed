#ifndef _ED_MESSAGES_LISTEN_H_
#define _ED_MESSAGES_LISTEN_H_

#include "message.h"
#include "../notifications/listener.h"

namespace ed
{
  struct listen_message
  {
    typedef message::word word;
    typedef message::byte byte;

    word event;
    word event_source_instance;
    byte event_source_module;

    byte listener_module;
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

      listener_module = e.module;
      listener_instance = e.instance;
    }

    operator message() const
    {
      message ret(5);
      byte *buffer = ret.payload->buf;
      *(word *)(buffer) = event;
      *(word *)(buffer + 1) = event_source_instance;
      buffer[3] = event_source_module;

      ret.event = reserved::event::LISTEN;
      ret.module = listener_module;
      ret.instance = listener_instance;
      return ret;
    }

    operator event_source() const
    {
      event_source es;
      es.event = event;
      es.module = event_source_module;
      es.instance = event_source_instance;
      return es;
    }

    operator slot_data::listener() const
    {
      slot_data::listener ret;
      ret.instance = listener_instance;
      ret.module = listener_module;
      return ret;
    }
  };
};

#endif