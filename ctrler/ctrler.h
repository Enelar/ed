#pragma once

#include <boost/asio.hpp>
#include <future>
#include <mutex>

using namespace std;

#include "library.h"
#include "message.h"
#include "connection.h"

class ctrler
{
  library names;

  int free_connection_id = ed::reserved::instance::FIRST_ALLOWED;
  unordered_map<int, connection> connections;
public:
  ctrler(int port);
  ~ctrler();

  void SendMessage(raw_message &, 
    int instance = ed::reserved::instance::BROADCAST, 
    int module = ed::reserved::module::BROADCAST);

private:
  bool exit_flag = false;
  mutex mutex_connections;
  future<void> accept_future;
  void AcceptThread(int port);
};