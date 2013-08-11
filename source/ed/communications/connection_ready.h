#ifndef _ED_COMMUNICATIONS_CONNECTION_READY_H_
#define _ED_COMMUNICATIONS_CONNECTION_READY_H_

#include "abstract_connection.h"

namespace ed
{
  namespace com
  {
    class __declspec(dllexport) connection_ready
    {
    public:
      virtual bool Ready() = 0;
      virtual abstract_connection *Read() = 0;
    };
  };
};

#endif