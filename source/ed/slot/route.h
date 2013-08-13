#ifndef _ED_SLOT_ROUTE_H_
#define _ED_SLOT_ROUTE_H_

#include "instance.h"

namespace ed
{
  namespace slot
  {
    class route
    {
      std::vector<instance> data;
    public:
      instance &GetInstance( const event_source & );
      module &GetModule( const event_source & );
      event &GetEvent( const event_source & );

      void AddListener( const listen_message & );
    };
  };
};

#endif