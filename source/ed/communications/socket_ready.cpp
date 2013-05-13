#include "socket_ready.h"
#include "../exceptions/exception.h"
#include "../3party/ax/tl4_low.h"

using namespace ed::com;
using namespace ax::tl4;
typedef ax::tl4::LOW_STATUSES low_status;

socket_ready::socket_ready( int port )
  : client(_TL4_NOT_SOCKET_), accept(_TL4_NOT_SOCKET_)
{
  low_status s = low::Open(accept, port, _TL4_MAX_CONNECTIONS);
  throw_assert(s == SUCCESS);
}

bool socket_ready::Ready()
{
  if (client != _TL4_NOT_SOCKET_)
    return true;
  unsafe_dword ip;
  unsafe_word port;
  client = low::Accept(accept, ip, port);
  return client != _TL4_NOT_SOCKET_;
}

#include "socket_connection.h"

abstract_connection *socket_ready::Read()
{
  unsigned int ret = client;
  client = _TL4_NOT_SOCKET_;
  return NEW socket_connection(ret);
}