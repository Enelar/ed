#ifndef _ED_KIT_EVENT_RESULT_H_
#define _ED_KIT_EVENT_RESULT_H_

#include "../messages/message.h"
#include "../notifications/event_types.h"

namespace ed
{
  class module;
  class __declspec(dllexport) event_result
  {
    mutable bool deactivated;

    module &m;
    message e;
    const int local_id;
    bool result;
    EVENT_RING r;

    friend class module;
    friend class module_impl;
    event_result( message &, module &, int local_id, bool result, EVENT_RING notify );
  public:
    event_result( const event_result & );

    operator bool &(); // change result commit or cancel
    operator bool() const;

    virtual ~event_result();
  };
};

#include "module.h"

#endif