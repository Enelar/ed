/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

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