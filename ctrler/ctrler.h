#pragma once

#include <boost/asio.hpp>
#include <future>

using namespace std;

class ctrler
{
public:
  ctrler(int port);
  ~ctrler();

  future<void> accept_future;
};