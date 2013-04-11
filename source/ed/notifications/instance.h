/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_EVENT_H_
#define _ED_NOTIFICATIONS_EVENT_H_

#include "event.h"

namespace ed
{
  namespace slot_data
  {
    typedef listeners_container <event> module;
    struct instance : public listeners_container<module>
    {
      void AddListener( int source_instance, int source_module, int source_event, listener destination )
      {
        todo("Add listener");
      }
    };
  };
};

#endif