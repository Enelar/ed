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
      event &GetEvent( const int i, bool force = false );
      event &GetEvent( const event_source &, bool force = false );

      void AddListener( const listen_message &, bool force = false );
    };
  };
};

#endif