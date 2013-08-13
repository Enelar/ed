#ifndef _ED_SLOT_INSTANCE_H_
#define _ED_SLOT_INSTANCE_H_

#include "module.h"
#include "../communications/abstract_connection.h"

namespace ed
{
  namespace slot
  {
    class instance
    {
      std::vector<module> data;
    public:
      com::abstract_connection *con;
      com::abstract_connection &Socket() const;

      module &GetModule( const int i );

      module &GetModule( const event_source & );
      event &GetEvent( const event_source & );

      void AddListener( const listen_message & );
    };
  };
};

#endif