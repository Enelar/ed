#pragma once

#include <boost/asio.hpp>
#include <future>

using namespace std;

#include "library.h"
#include "message.h"

class ctrler
{
  library names;
public:
  ctrler(int port);
  ~ctrler();

  future<void> accept_future;
  void SendMessage(raw_message &, 
    int instance = ed::reserved::instance::BROADCAST, 
    int module = ed::reserved::module::BROADCAST);
};