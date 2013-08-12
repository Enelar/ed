#ifndef _ED_COMMUNITCATIONS_SOCKET_CONNECTION_H_
#define _ED_COMMUNITCATIONS_SOCKET_CONNECTION_H_

#include "abstract_connection.h"
#include "../notifications/event_notification.h"
#include <string>

namespace ed
{
  namespace com
  {
    class _ED_DLL_EXPORT_ socket_connection : public abstract_connection
    {
      unsigned int desc;
      bool connected;

      void ConnectAttempt();
      void ConnectAttempt( unsigned int ip, int port );
      socket_connection( int icoming_descriptor );

      void SendMessage( const message &m );
    public:
      socket_connection( const std::string &addr, int port );

      virtual void Notify( const ed::event_notification & );
      virtual int Incoming( );

      virtual void SendRegister( const register_message & );
      virtual message Get();

      ~socket_connection();
      friend class socket_ready;
    };
  };
};

#endif