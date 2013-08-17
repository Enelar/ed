#ifndef _ED_COMMUNITCATIONS_SOCKET_CONNECTION_H_
#define _ED_COMMUNITCATIONS_SOCKET_CONNECTION_H_

#include "abstract_connection.h"
#include "../notifications/event_notification.h"
#include <string>

namespace ed
{
  namespace com
  {
    class socket_connection : public abstract_connection
    {
      unsigned int desc;
      bool connected;
      const std::string addr;
      unsigned int ip;
      const unsigned int port;

      void ConnectAttempt();
      void ConnectAttempt( unsigned int ip, int port );
      socket_connection( int icoming_descriptor, int ip, int port );

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