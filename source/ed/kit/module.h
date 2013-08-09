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

    template<typename T, typename MODULE, typename RET>
    void SysCreateHandler( RET (MODULE::*f)( const event_context<T> & ), event_source es )
    {
      typedef event_handler_convert<T, RET> adapterT;
      adapterT *test = NEW adapterT(f);
      callback_entry<unused_internal_type, RET> obj(es, test);

      /*
      callback_entry<post_event_handler_t> t;
  t.callback = q;
  t.source = source;
  EventCallbacks.push_back(t);
  gw.Listen(source.instance, id, source.module, adapter.ToGlobal(source.event));       
  */
    }
  private:
    template<typename callback_type, typename RET>
    struct callback_entry
    {
      event_source source;
      event_handler_convert<callback_type, RET> *callback;

      callback_entry( event_source es, event_handler_convert<callback_type, RET> *t )
        : callback(t), source(es)
      {}
      ~callback_entry()
      {
        delete callback;
      }
    };

    typedef callback_entry<unused_internal_type, bool> base_pre_callback_entry;
    typedef callback_entry<unused_internal_type, void> base_post_callback_entry;
    std::vector<base_pre_callback_entry> QueryCallbacks;
    std::vector<base_post_callback_entry> EventCallbacks;

    void EventReciever( const message & );
    bool Query( const message & );
  };
};

#endif