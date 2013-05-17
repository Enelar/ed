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
    void Listen( int instance, std::string module, std::string event );
    
    event_result SendEvent( 
      int local_id,
      buffer payload,
      EVENT_RING query_max_ring = RING0_THREAD,
      EVENT_RING notify_max_ring = RING3_WORLD );
    event_result SendEvent( 
      int local_id,
      EVENT_RING query_max_ring = RING0_THREAD,
      EVENT_RING notify_max_ring = RING3_WORLD );
      
    struct event_context
    {
      int event_local_id;
      const event_source &source;
      buffer *const payload;
      
      event_context( int _event_local_id, const event_source &_source, buffer *const _payload  )
        : event_local_id(_event_local_id), source(_source), payload(_payload)
      {
      }
    };

    typedef bool (module::*query_callback_type)( const event_context & );
    typedef void (module::*event_callback_type)( const event_context & );

  protected:

    void RegisterQueryCallback( query_callback_type, int source_instance, std::string event, std::string module );
    void RegisterQueryCallback( query_callback_type, event_source );
    void RegisterEventCallback( event_callback_type, int source_instance, std::string event, std::string module );
    void RegisterEventCallback( event_callback_type, event_source );
  private:
    template<typename callback_type>
    struct callback_entry
    {
      event_source source;
      callback_type callback;
    };
    std::vector<callback_entry<query_callback_type>> QueryCallbacks;
    std::vector<callback_entry<event_callback_type>> EventCallbacks;

    void EventReciever( const message & );
    bool Query( const message & );
  };
};

#endif