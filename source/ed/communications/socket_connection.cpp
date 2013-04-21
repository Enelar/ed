/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

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
  while ((s = ax::tl4::low::Send(desc, m.buffer, m.len)) == PLEASE_WAIT)
    Sleep(1);
  if (s == SUCCESS)
    return;
  EXCEPTION(disconnected);
}

message *socket_connection::Get()
{
  typedef unsigned char byte;
  // looks like crap code
  MESSAGE_TYPE mt = (MESSAGE_TYPE)0;
  word readed;
  low_status s = ax::tl4::low::Recieve(desc, (byte *)&mt, readed, 1);
  if (s == NO_MESSAGES)
    return NULL;
  if (s == DISCONNECT)
    EXCEPTION(disconnected);
  byte expected_size = 0, t = 0;
  message *ret = NULL;
  switch (mt)
  {
  case REGISTER:
    throw_assert(
      ax::tl4::low::Recieve(desc, (byte *)&t, readed, 1) == SUCCESS);
    throw_assert(
      ax::tl4::low::Recieve(desc, (byte *)&expected_size, readed, 1) == SUCCESS);

    ret = NEW message(sizeof(char) * 3 + expected_size);
    ret->buffer[0] = (char)mt;
    ret->buffer[1] = t;
    ret->buffer[2] = expected_size;
    throw_assert(ax::tl4::low::Recieve(desc, (byte *)ret->buffer + 3, readed, expected_size) == SUCCESS);
    throw_sassert(readed == expected_size, "TODO: Message not readed at first try/not completed");
    return ret;
    break;
  case LISTEN:
    expected_size = sizeof(char) + sizeof(word) + sizeof(char);
    break;
  case NOTIFY:
    expected_size = sizeof(char) + sizeof(word) + sizeof(char) + + sizeof(word);
    break;
  default:
    dead_space();
  }
  dead_space();
  ret = NEW message(1 + expected_size);
  ret->buffer[0] = (char)mt;
  throw_assert(ax::tl4::low::Recieve(desc, (byte *)ret->buffer + 1, readed, ret->len) == SUCCESS);
  throw_sassert(readed == ret->len, "TODO: Message not readed at first try/not completed")
  return ret;
}