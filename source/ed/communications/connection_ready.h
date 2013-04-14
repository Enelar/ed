/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_COMMUNICATIONS_CONNECTION_READY_H_
#define _ED_COMMUNICATIONS_CONNECTION_READY_H_

#include "abstract_connection.h"

namespace ed
{
  namespace com
  {
    class connection_ready
    {
    public:
      virtual bool Ready() = 0;
      virtual abstract_connection *Read() = 0;
    };
  };
};

#endif