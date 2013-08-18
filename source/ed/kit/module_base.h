#ifndef _ED_KIT_MODULE_BASE_H_
#define _ED_KIT_MODULE_BASE_H_

#include "gateway.h"
#include "../names/translate.h"
#include "../names/reserved.h"
#include "event_context.h"
#include "event_handler_convert.h"

#include "../3party/ax/types.h"
#include "module_impl.h"

namespace ed
{
  class module_base : public ax::object
  {
  public:
    template<typename MODULE, typename RET, typename T = event_data>
    struct event_handler
    {
      typedef RET (MODULE::*t)( const event_context<T> & );
    };

    typedef event_handler<module_base, bool>::t pre_event_handler_t;
    typedef event_handler<module_base, void>::t post_event_handler_t;

    typedef module_impl::base_pre_callback_entry base_pre_callback_entry;
    typedef module_impl::base_post_callback_entry base_post_callback_entry;

    module_base( const std::string &, gateway & );
    ~module_base();
  protected:
    template<typename T, typename MODULE>
    void RegisterPreHandler( bool (MODULE::*f)( const event_context<T> & ), event_source es );

    template<typename T, typename MODULE>
    void RegisterPostHandler( void (MODULE::*f)( const event_context<T> & ), event_source es );

    template<typename MODULE>
    void UnregisterHandlers( const MODULE *const );

    void RegisterEvent( const std::string &name, int local_id );
  private:
    template<typename T, typename MODULE, typename RET>
    module_impl::callback_entry<typename RET> *SysCreateHandler( RET (MODULE::*f)( const event_context<T> & ), event_source es );

    void EventReciever( const message & );
    bool Query( const message & );
    void Listen( int instance, const std::string &module, const std::string &event );

    friend class gateway;
    friend class gateway_impl;
    friend class event_result;
    friend class module;
    module_base( int id, gateway & );
    bool SendPreEvent( int local_id, message & );
    void SendPostEvent( int local_id, message & );

    module_impl &impl;
  };
};


#include "module_base.hpp"

#endif