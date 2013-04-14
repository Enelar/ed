/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_COMMUNITCATIONS_ABSTRACT_CONNECTION_H_
#define _ED_COMMUNITCATIONS_ABSTRACT_CONNECTION_H_

#include "../notifications/event_notification.h"
#include "../messages/register.h"

namespace ed
{
  namespace com
  {
    class abstract_connection
    {
    public:
      virtual void Notify( const event_notification & ) = 0;
      virtual int Incoming( ) = 0;

      virtual void SendRegister( const register_message & ) = 0;
      virtual message Get() = 0;

      virtual ~abstract_connection() = 0;
    };
  };
};

#include "connection_ready.h"

#endif