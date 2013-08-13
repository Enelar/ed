#ifndef _ED_SLOT_EVENT_H_
#define _ED_SLOT_EVENT_H_

#include "../notifications/event_source.h"
#include "../notifications/listener.h"
#include "../messages/listen.h"
#include <vector>

namespace ed
{
  struct slot_not_found
  {
  };
  namespace slot
  {
    struct event
    {
      std::vector<slot_data::listener> data;

      void AddListener( const listen_message &, bool force = true );
      void AddListener( const slot_data::listener &, bool force = true );
    private:
      bool ListenerExist( const slot_data::listener & ) const;
    };
  };
};

#endif