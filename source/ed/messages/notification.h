#ifndef _ED_MESSAGES_NOTIFICATION_H_
#define _ED_MESSAGES_NOTIFICATION_H_

#include "../notifications/event_notification.h"

namespace ed
{
  struct notification_message : public event_notification
  {
  public:
    register_message( message &e )
    {
      throw_assert(e.GetType() == NOTIFY);
    }
  };
};

#endif