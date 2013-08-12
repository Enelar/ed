#ifndef _ED_SLOT_EVENT_H_
#define _ED_SLOT_EVENT_H_

#include "../notifications/event_source.h"
#include "../notifications/listener.h"
#include <vector>

namespace ed
{
  namespace slot
  {
    struct event
    {
      std::vector<slot_data::listener> data;
    };
  };
};

#endif