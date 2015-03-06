#pragma once

#include <boost/asio.hpp>
#include <future>
#include <ed\structs\semaphore.h>

using namespace std;

#include <ed\structs\library.h>
#include <ed\structs\message.h>
#include "connection.h"
#include "dispatcher.h"

namespace messages
{
  struct handshake;
}

class ctrler
{
  library names;

  int free_connection_id = ed::reserved::instance::FIRST_ALLOWED;
  unordered_map<int, connection> connections;
  unordered_map<int, modules_container> exceptional_listen;

  dispatcher core;
  friend class dispatcher;

  boost::asio::io_service 
    &accept_io, // async
    message_io; // sync
  boost::asio::ip::tcp::acceptor accept_socket;
public:
  ctrler(boost::asio::io_service &, int port);
  ~ctrler();

  void Send(raw_message);
  void Send(raw_message, int instance);

  void OnMessage(int, raw_message);
  void OnHandshake(int, ::messages::handshake);

private:
  bool exit_flag = false;
  semaphore_strict mutex_connections;
  future<void> accept_future, message_future;
  void AcceptThread(int port);
  void MessageThread();
};