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
  class module_base;
  class module_impl
  {
  public:
    module_impl( module_base &, const std::string &, gateway & );
    virtual ~module_impl();
    void RegisterEvent( const std::string &name, int local_id );
    void Listen( int instance, const std::string &module, const std::string &event );

    const translate &GetAdapter() const;
    int NameGlobalID( const std::string &name, NAME_TYPE nt );

    event_result SendEvent( int local_id, buffer payload, EVENT_RING query_max_ring, EVENT_RING notify_max_ring);
    event_result SendEvent( int local_id, EVENT_RING query_max_ring, EVENT_RING notify_max_ring );

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

    typedef callback_entry<bool> base_pre_callback_entry;
    typedef callback_entry<void> base_post_callback_entry;
    void AddPreHandler( base_pre_callback_entry *obj );
    void AddPostHandler( base_post_callback_entry *obj );

    std::vector<base_pre_callback_entry *> QueryCallbacks;
    std::vector<base_post_callback_entry *> EventCallbacks;

    void EventReciever( const message & );
    bool Query( const message & );

    module_base &m;
    friend class module_base;
    friend class gateway_impl;
    friend class event_result;
    module_impl( module_base &, int id, gateway & );
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
  };
};

#endif