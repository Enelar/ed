#ifndef _ED_KIT_MODULE_H_
#define _ED_KIT_MODULE_H_

#include "module_base.h"

#include "event_result.h"
#include "../notifications/event_types.h"

namespace ed
{
  class module : public module_base
  {
    module( int id, gateway & );
  public:
    module( const std::string &, gateway & );
    virtual ~module();
    
    event_result SendEvent( 
      int local_id,
      buffer payload,
      EVENT_RING query_max_ring = RING0_THREAD,
      EVENT_RING notify_max_ring = RING3_WORLD );
    event_result SendEvent( 
      int local_id,
      EVENT_RING query_max_ring = RING0_THREAD,
      EVENT_RING notify_max_ring = RING3_WORLD );
  };
};

#endif