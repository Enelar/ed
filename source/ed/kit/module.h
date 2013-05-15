#ifndef _ED_KIT_MODULE_H_
#define _ED_KIT_MODULE_H_

#include "gateway.h"
#include "../names/translate.h"
#include "event_result.h"
#include "../notifications/event_types.h"

namespace ed
{
  class module
  {
    friend class gateway;
    friend class event_result;
    module( int id, gateway & );
    gateway &gw;
    int id;
    translate adapter;
    bool SendPreEvent( int local_id, message & );
    void SendPostEvent( int local_id, message & );
    struct event_listeners
    {
      std::list<int> modules;
    };
    std::vector<event_listeners> pre_listeners;
  public:
    void RegisterEvent( std::string name, int local_id );
    
    event_result SendEvent( 
      int local_id,
      buffer payload,
      EVENT_RING query_max_ring = RING0_THREAD,
      EVENT_RING notify_max_ring = RING3_WORLD );
    event_result SendEvent( 
      int local_id,
      EVENT_RING query_max_ring = RING0_THREAD,
      EVENT_RING notify_max_ring = RING3_WORLD );
      
    virtual void EventReciever( const event_notification & )
    {
    }
    virtual bool Query( const event_notification & )
    {
      return true;
    }
  };
};

#endif