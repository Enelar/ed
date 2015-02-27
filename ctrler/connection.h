#pragma once

#include <future>
#include <memory>
using namespace std;

struct raw_connection
{

};

struct connection
{
  bool handler;
  bool disconnected = false;

  shared_ptr<raw_connection> raw;

  operator bool() const;

  connection(bool);
  connection(const connection &);
  ~connection();

  bool exit_flag = false;
  future<void> receive_thread;
  void ReceiveThread();
};