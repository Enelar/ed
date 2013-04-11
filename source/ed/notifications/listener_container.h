/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_LISTENER_CONTAINER_H_
#define _ED_NOTIFICATIONS_LISTENER_CONTAINER_H_

#include "slot_data.h"
#include "event_notification.h"

namespace ed
{
  namespace slot_data
  {
    class RemoveInstance;
    template<typename child_type>
    struct listeners_container : public common_container<child_type>
    {
      void RemoveDisconnectedInstance( int id )
      {
        Each(RemoveInstance(id));
      }
      void AddListener( event_source source, listener dest )
      {
        AddListener *al = NEW slot_data::AddListener(source, dest)
        al->Direct(*this);
        delete al;
      }
    };
  };
};

#include "slot_data_utils.h"

#endif