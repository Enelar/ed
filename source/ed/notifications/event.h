/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_EVENT_H_
#define _ED_NOTIFICATIONS_EVENT_H_

#include "listener_container.h"

namespace ed
{
  enum EVENT_STATE
  {
    PRE_CHANGE,
    PRE_LISTEN,
    POST_COMMIT,
    POST_CANCEL
  };

  namespace slot_data
  {
    struct event : public listeners_container<listener>
    {
      template<typename obj_type>
      void Each( obj_type &a )
      {
        a.Commit(*this);
      }
    };
  };
};

#endif