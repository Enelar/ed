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
    module( const std::string &, gateway & );
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

    typedef bool (*query_callback_type)( const int event_local_id, const event_source &source, const buffer *const payload );
    typedef void (*event_callback_type)( const int event_local_id, const event_source &source, const buffer *const payload );

  protected:
    typedef query_callback_type module::* query_callback_entry_type;
    typedef event_callback_type module::* event_callback_entry_type;

    void RegisterQueryCallback( query_callback_entry_type, event_source );
    void RegisterEventCallback( event_callback_entry_type, event_source );
  private:
    template<typename callback_type>
    struct callback_entry
    {
      event_source source;
      callback_type callback;
    };
    std::vector<callback_entry<query_callback_entry_type>> QueryCallbacks;
    std::vector<callback_entry<event_callback_entry_type>> EventCallbacks;

    void EventReciever( const message & );
    bool Query( const message & );
  };
};

#endif