#ifndef _ED_KIT_MODULE_IMPL_H_
#define _ED_KIT_MODULE_IMPL_H_

#include "gateway.h"
#include "../names/translate.h"
#include "event_result.h"
#include "../notifications/event_types.h"
#include "../names/reserved.h"
#include "event_context.h"
#include "event_handler_convert.h"

namespace ed
{
  class module_impl
  {
    module &m;
    friend class module;
    friend class gateway;
    friend class gateway_impl;
    friend class event_result;
    module_impl( module &, int id, gateway & );
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
    module_impl( module &, const std::string &, gateway & );
    virtual ~module_impl();
    void RegisterEvent( const std::string &name, int local_id );
    void Listen( int instance, const std::string &module, const std::string &event );
    
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

  private:
    template<typename RET>
    struct callback_entry
    {
      event_source source;
      event_handler_adapter<RET> *callback;

      callback_entry( event_source es, event_handler_adapter<RET> *t )
        : callback(t), source(es)
      {}
      ~callback_entry()
      {
        delete callback;
      }
    };
    void AddPreHandler( callback_entry<bool> *obj )
    {
      QueryCallbacks.push_back(obj);
    }
    void AddPostHandler( callback_entry<void> *obj )
    {
      EventCallbacks.push_back(obj);
    }
  protected:
    template<typename T, typename MODULE>
    void RegisterPreHandler( bool (MODULE::*f)( const event_context<T> & ), event_source es )
    {
      callback_entry<bool> *obj = SysCreateHandler<T, MODULE, bool>(f, es);
      QueryCallbacks.push_back(obj);
    }

    template<typename T, typename MODULE>
    void RegisterPostHandler( void (MODULE::*f)( const event_context<T> & ), event_source es )
    {
      callback_entry<void> *obj = SysCreateHandler<T, MODULE, void>(f, es);
      EventCallbacks.push_back(obj);
    }

  private:
    template<typename T, typename MODULE, typename RET>
    callback_entry<typename RET> *SysCreateHandler( RET (MODULE::*f)( const event_context<T> & ), event_source es )
    {
      typedef event_handler_convert<MODULE, T, RET> adapterT;
      adapterT *test = NEW adapterT(static_cast<MODULE &>(*this), f);
      return NEW callback_entry<RET>(es, test);
    }

    template<typename MODULE>
    void UnregisterHandlers()
    {
      for (unsigned int i = 0; i < QueryCallbacks.size(); ++i)
        delete QueryCallbacks[i];
      for (unsigned int i = 0; i < EventCallbacks.size(); ++i)
        delete EventCallbacks[i];
    }

    typedef callback_entry<bool> base_pre_callback_entry;
    typedef callback_entry<void> base_post_callback_entry;
    std::vector<base_pre_callback_entry *> QueryCallbacks;
    std::vector<base_post_callback_entry *> EventCallbacks;

    void EventReciever( const message & );
    bool Query( const message & );
  };
};

#endif