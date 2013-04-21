/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_EVENT_NOTIFICATION_H_
#define _ED_NOTIFICATIONS_EVENT_NOTIFICATION_H_

#include "../def.h"
#include "../messages/message.h"

namespace ed
{
  struct event_source
  {
    int instance, module, event;
  };

  struct event_notification
  {
    event_source source;
    int target_module;
    const int payload_size;
    char *payload;
    event_notification( int size )
      : payload_size(size), payload(NEW char[size]),
      target_module(0)
    {
    }

    static const int
      sizeof_magic = 1,
      sizeof_target_module = 1,
      sizeof_source_event = 2,
      sizeof_source_module = 1,
      sizeof_source_instance = 2,
      sizeof_payload_size = 1;
    static const int
      head_size = 
        sizeof_payload_size +
        sizeof_target_module +
        sizeof_source_event +
        sizeof_source_module +
        sizeof_source_instance;

    operator message() const
    {
      throw_assert(payload_size < 256 && payload_size >= 0);
      int len = 
        sizeof_magic +
        head_size +
        payload_size;
      message m(len);
      char *buffer = (char *)m.buffer;
      buffer[0] = NOTIFY;
      buffer += sizeof_magic;

      buffer[0] = payload_size;
      buffer += sizeof_payload_size;

      buffer[0] = (char)target_module;
      buffer += sizeof_target_module;

      ((short *)buffer)[0] = source.event;
      buffer += sizeof_source_event;

      buffer[0] = source.module;
      buffer += sizeof_source_module;

      ((short *)buffer)[0] = source.instance;
      buffer += sizeof_source_instance;

      memcpy(buffer, payload, payload_size);
      return m;
    }

    event_notification( const message &m )
      : payload_size(
        m.buffer[sizeof_magic]
                    ),
        payload(NULL)
    {
      char *buffer = (char *)m.buffer;
      throw_assert(buffer[0] == NOTIFY);
      buffer += sizeof_magic;
      //payload_size = buffer[0];
      buffer += sizeof_payload_size;
      target_module = buffer[0];
      buffer += sizeof_target_module;
      source.event = ((short *)buffer)[0];
      buffer += sizeof_source_event;
      source.module = buffer[0];
      buffer += sizeof_source_module;
      source.instance = ((short *)buffer)[0];
      buffer += sizeof_source_instance;
      payload = NEW char[payload_size];
      memcpy(payload, buffer, payload_size);
    }
    ~event_notification()
    {
      if (payload)
        delete payload;
    }
  };
};

#endif
