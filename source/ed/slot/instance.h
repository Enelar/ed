#ifndef _ED_SLOT_INSTANCE_H_
#define _ED_SLOT_INSTANCE_H_

#include "module.h"

namespace ed
{
  namespace slot
  {
    class instance
    {
      std::vector<module> data;
    public:
      module &GetModule( const event_source & );
      event &GetEvent( const event_source & );
    };
  };
};

#endif