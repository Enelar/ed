#ifndef _ED_KIT_MODULE_H_
#define _ED_KIT_MODULE_H_

#include "gateway.h"
#include "../names/translate.h"
#include "event_result.h"
#include "../notifications/event_types.h"
#include "../names/reserved.h"
#include "event_context.h"
#include "event_handler_convert.h"

#include "module_impl.h"
namespace ed
{
  class module
  {
  public:
    typedef bool (module::*pre_event_handler_t)( const event_context<> & );
    typedef void (module::*post_event_handler_t)( const event_context<> & );

    typedef module_impl::base_pre_callback_entry base_pre_callback_entry;
    typedef module_impl::base_post_callback_entry base_post_callback_entry;
  private:

    module_impl &impl;
    friend class gateway;
    friend class gateway_impl;
    friend class event_result;
    module( int id, gateway & );
    bool SendPreEvent( int local_id, message & );
    void SendPostEvent( int local_id, message & );
    struct event_listeners
    {
      std::list<int> modules;
    };
  public:
    module( const std::string &, gateway & );
    virtual ~module();
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
      


  private:
  protected:
    template<typename T, typename MODULE>
    void RegisterPreHandler( bool (MODULE::*f)( const event_context<T> & ), event_source es );

    template<typename T, typename MODULE>
    void RegisterPostHandler( void (MODULE::*f)( const event_context<T> & ), event_source es );

    void AddPreHandler( base_pre_callback_entry *obj );
    void AddPostHandler( base_post_callback_entry *obj );

    template<typename MODULE>
    void UnregisterHandlers( const MODULE *const );
  private:
    template<typename T, typename MODULE, typename RET>
    module_impl::callback_entry<typename RET> *SysCreateHandler( RET (MODULE::*f)( const event_context<T> & ), event_source es );

    void EventReciever( const message & );
    bool Query( const message & );
  };
};

#include "module.hpp"

#endif