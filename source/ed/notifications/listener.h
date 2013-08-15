#ifndef _ED_NOTIFICATIONS_LISTENER_H_
#define _ED_NOTIFICATIONS_LISTENER_H_

#include "../exceptions/exception.h"
#include "event_source.h"

namespace ed
{
  namespace slot_data
  {
    struct listener
    {
      int instance, module;

      bool operator==( const listener &a ) const
      {
        return instance == a.instance && module == a.module;
      }
      bool operator==( const event_source &a ) const
      {
        throw_assert(a.instance && a.module);
        return instance == a.instance && module == a.module;
      }
    };
  };
};

#endif