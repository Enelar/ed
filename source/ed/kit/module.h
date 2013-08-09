#ifndef _ED_KIT_MODULE_H_
#define _ED_KIT_MODULE_H_

#include "gateway.h"
#include "../names/translate.h"
#include "event_result.h"
#include "../notifications/event_types.h"
#include "../names/reserved.h"
#include "event_context.h"
#include "event_handler_convert.h"

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
      
    typedef bool (module::*pre_event_handler_t)( const event_context<> & );
    typedef void (module::*post_event_handler_t)( const event_context<> & );

  protected:

    //void SetPreEventHandler( pre_event_handler_t, std::string event, 
//      std::string module = "", int source_instance = reserved::instance::BROADCAST );
    template<typename T, typename MODULE>
    void SetPreEventHandler( bool (MODULE::*f)( const event_context<T> & ), event_source es )
    {
      SetPreEventHandler(reinterpret_cast<pre_event_handler_t>(f), es);
    }
    void SetPreEventHandler( pre_event_handler_t, event_source );
  //  void SetPostEventHandler( post_event_handler_t, std::string event,
      //std::string module = "", int source_instance = reserved::instance::BROADCAST );
    template<typename T, typename MODULE>
    void SetPostEventHandler( void (MODULE::*f)( const event_context<T> & ), event_source es )
    {
      SetPostEventHandler(reinterpret_cast<post_event_handler_t>(f), es);
    }
    void SetPostEventHandler( post_event_handler_t, event_source );
  private:
    template<typename callback_type>
    struct callback_entry
    {
      event_source source;
      callback_type callback;
    };
    std::vector<callback_entry<pre_event_handler_t>> QueryCallbacks;
    std::vector<callback_entry<post_event_handler_t>> EventCallbacks;

    void EventReciever( const message & );
    bool Query( const message & );
  };
};

#endif