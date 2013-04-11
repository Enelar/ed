/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_EVENT_NOTIFICATION_H_
#define _ED_NOTIFICATIONS_EVENT_NOTIFICATION_H_

namespace ed
{
  struct event_source
  {
    int instance, module, event;
  };

  struct event_notification
  {
    event_source source;
    int payload_size;
    char *payload;
  };
};

#endif
