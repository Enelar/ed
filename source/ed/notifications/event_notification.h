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
      todo(event notification to message);
    }

    event_notification( const message &m )
      : payload_size(
        0 //m.buffer[sizeof_magic]
                    ),
        payload(NULL)
    {
      todo(event_notification constructor);

      todo(message to event notification);
    }
    ~event_notification()
    {
      if (payload)
        delete payload;
    }
  };
};

#endif
