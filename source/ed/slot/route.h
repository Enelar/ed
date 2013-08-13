#ifndef _ED_SLOT_ROUTE_H_
#define _ED_SLOT_ROUTE_H_

#include "instance.h"

namespace ed
{
  namespace slot
  {
    class route
    {
    public:
      std::vector<instance> data;

      instance &GetInstance( const int i );
      instance &GetInstance( const event_source & );
      module &GetModule( const event_source & );
      event &GetEvent( const event_source & );

      void AddListener( const listen_message & );
      void AddListener( const event_source &, const slot_data::listener & );
    };
  };
};

#endif