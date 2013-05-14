#ifndef _ED_KIT_MODULE_H_
#define _ED_KIT_MODULE_H_

#include "gateway.h"
#include "../names/translate.h"
#include "event_result.h"

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

    bool SendPreEvent( int local_id );
    void SendPostEvent( int local_id );
    bool SendPreEvent( int local_id, buffer payload );
    void SendPostEvent( int local_id, buffer payload );
  public:
    void RegisterEvent( std::string name, int local_id );
    event_result SendEvent( int local_id );
  };
};

#endif