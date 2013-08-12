#ifndef _ED_NOTIFICATIONS_EVENT_NOTIFICATION_H_
#define _ED_NOTIFICATIONS_EVENT_NOTIFICATION_H_

#include "../def.h"
#include "../messages/message.h"
#include "../names/reserved.h"

namespace ed
{
  struct _ED_DLL_EXPORT_ event_source
  {
    int instance, module, event;
    
    event_source() :
      event(reserved::event::BROADCAST), 
      module(reserved::module::BROADCAST),
      instance(reserved::instance::BROADCAST)
    {
    }

    bool operator==( const event_source &a ) const
    {
      return instance == a.instance && module == a.module && event == a.event;
    }
  };

  struct _ED_DLL_EXPORT_ event_notification
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
  private:
    enum sizeofs
    {
      sizeof_magic = 1,
      sizeof_target_module = 1,
      sizeof_source_event = 2,
      sizeof_source_module = 1,
      sizeof_source_instance = 2,
      sizeof_payload_size = 1,
      head_size = 
          sizeof_payload_size +
          sizeof_target_module +
          sizeof_source_event +
          sizeof_source_module +
          sizeof_source_instance
    };

  public:
    operator message() const;
    operator event_source() const
    {
      return source;
    }

    event_notification( const message &m );
    
    ~event_notification()
    {
      if (payload)
        delete payload;
    }
  };
};

#endif
