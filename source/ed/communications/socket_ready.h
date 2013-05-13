#ifndef _ED_COMMUNICATIONS_SOCKET_READY_H_
#define _ED_COMMUNICATIONS_SOCKET_READY_H_

#include "connection_ready.h"
#include "socket_connection.h"

namespace ed
{
  namespace com
  {
    class socket_ready : public connection_ready
    {
      unsigned int accept, client;
    public:
      socket_ready( int port );
      virtual bool Ready();
      virtual abstract_connection *Read();
      typedef ed::com::socket_connection pair_type;
    };
  };
};

#endif