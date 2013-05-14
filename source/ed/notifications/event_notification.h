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
    event_notification( buffer _payload )
      : payload_size(_payload.len), payload(NULL)
    {
      if (!payload_size)
        return;
      payload = NEW char[payload_size];
      memcpy(payload, _payload.buf, payload_size);
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

    operator message() const;

    event_notification( const message &m );
    
    ~event_notification()
    {
      if (payload)
        delete payload;
    }
  };
};

#endif
