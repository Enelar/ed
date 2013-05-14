#include "../exceptions/exception.h"
#include "socket_connection.h"
#include "../3party/ax/tl4_low.h"

using namespace ed::com;
using namespace ed;
using namespace ax::tl4;
typedef ax::tl4::LOW_STATUSES low_status;

socket_connection::socket_connection( std::string addr, int port )
 : connected(false), desc(_TL4_NOT_SOCKET_)
{
  unsigned int ip;
  low_status s = low::GetIp(addr.c_str(), ip);
  throw_assert(s != CANT_RESOLVE_IP);
  throw_assert(s == SUCCESS);
  ConnectAttempt(ip, port);
}

socket_connection::socket_connection( int incoming_descriptor )
  : connected(true), desc(incoming_descriptor)
{
}

void socket_connection::ConnectAttempt()
{
  ConnectAttempt(0, 0); // cause they ignoring after first call
}

void socket_connection::ConnectAttempt( unsigned int ip, int port )
{
  if (connected)
    return;
  low_status s = low::Connect(desc, ip, (unsafe_word)port);
  throw_assert(s != LOW_CONNECTION_REFUSED);
  if (s == SUCCESS)
    connected = true;
}

void socket_connection::Notify( const ed::event_notification &e )
{
  message m = e;
  SendMessage(m);
}

int socket_connection::Incoming( )
{
  ConnectAttempt();
  if (!connected)
    return 0;
  return low::Incoming(desc);
}

socket_connection::~socket_connection()
{
  if (desc != _TL4_NOT_SOCKET_)
    low::Close(desc);
}


void socket_connection::SendRegister( const register_message &name )
{
  message m = name;
  SendMessage(m);
}

#include "../3party/win/utils.h"
#include "../exceptions/disconnected.h"

void socket_connection::SendMessage( const message &m )
{
  ConnectAttempt();
  low_status s;
  buffer b = m;
  while ((s = ax::tl4::low::Send(desc, b.buf, b.len)) == PLEASE_WAIT)
    Sleep(1);
  if (s == SUCCESS)
    return;
  EXCEPTION(disconnected);
}

template<typename type>
void SuccessRecieve( unsigned int socket, type *buffer, int size )
{
  word readed;
  ax::tl4::LOW_STATUSES res = ax::tl4::low::Recieve(socket, (byte *)buffer, readed, size);
  throw_assert(res == SUCCESS);
  throw_assert(readed == size);
}

message *socket_connection::Get()
{
  if (Incoming() < message::MinRequiredSize())
    return NULL;
  flag_byte flags;
  SuccessRecieve(desc, &flags, 1);
  int header_size = message::ExpectedSize(flags);
  throw_assert(Incoming() >= header_size - 1);
  buffer b(header_size);
  b.buf[0] = *reinterpret_cast<byte *>(&flags);

  SuccessRecieve(desc, b.buf + 1, header_size - 1);

  message *ret = NEW message(b);
  int expected_payload = ret->ExpectedPayloadSize();
  if (expected_payload)
    ret->payload = NEW buffer(expected_payload);
  SuccessRecieve(desc, ret->payload->buf, expected_payload);
  return ret;
}