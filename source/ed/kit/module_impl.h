#ifndef _ED_KIT_MODULE_IMPL_H_
#define _ED_KIT_MODULE_IMPL_H_

#include "gateway.h"
#include "../names/translate.h"
#include "event_result.h"
#include "../notifications/event_types.h"
#include "../names/reserved.h"

namespace ed
{
  class module_ed
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