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
      module &GetModule( const event_source &, bool force = false );
      event &GetEvent( const event_source &, bool force = false );

      void AddListener( const listen_message &, bool force = false );
      void AddListener( const event_source &, const slot_data::listener &, bool force = false );

      int AddInstance( com::abstract_connection * );
      void RemoveDisconnected( const int instance );

      std::set<int> SubscribedInstances( const event_source &es );
    };
  };
};

#endif