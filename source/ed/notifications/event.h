#ifndef _ED_NOTIFICATIONS_EVENT_H_
#define _ED_NOTIFICATIONS_EVENT_H_

#include "listener_container.h"

namespace ed
{
  namespace slot_data
  {
    struct _ED_DLL_EXPORT_ event : public listeners_container<listener>
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