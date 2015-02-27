#pragma once

#include <boost/asio.hpp>
#include <future>
#include <mutex>

using namespace std;

#include "library.h"
#include "message.h"
#include "connection.h"
#include "dispatcher.h"

class ctrler
{
  library names;

  int free_connection_id = ed::reserved::instance::FIRST_ALLOWED;
  unordered_map<int, connection> connections;

  dispatcher core;
  friend class dispatcher;
public:
  ctrler(int port);
  ~ctrler();

  void Send(raw_message);
  void Send(raw_message, int instance);

  void OnMessage(int, raw_message);

private:
  bool exit_flag = false;
  mutex mutex_connections;
  future<void> accept_future, message_future;
  void AcceptThread(int port);
  void MessageThread();
};