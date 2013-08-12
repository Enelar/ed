#ifndef _ED_SLOT_MODULE_H_
#define _ED_SLOT_MODULE_H_

#include "event.h"

namespace ed
{
  namespace slot
  {
    class module
    {
      std::vector<event> data;
    public:
      event &GetEvent( const event_source & );
    };
  };
};

#endif