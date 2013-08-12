#ifndef _ED_COMMUNITCATIONS_ABSTRACT_CONNECTION_H_
#define _ED_COMMUNITCATIONS_ABSTRACT_CONNECTION_H_

#include "../notifications/event_notification.h"
#include "../messages/register.h"

namespace ed
{
  namespace com
  {
    class _ED_DLL_EXPORT_ abstract_connection
    {
    public:
      virtual void Notify( const event_notification & ) = 0;
      virtual int Incoming( ) = 0;

      virtual void SendRegister( const register_message & ) = 0;
      virtual message Get() = 0;

      virtual ~abstract_connection()
      {
      };
    };
  };
};

#include "connection_ready.h"

#endif