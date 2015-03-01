#pragma once

#include <future>
#include <memory>
#include <mutex>
#include <list>
using namespace std;

#include <ed\structs\message.h>
#include "containers.h"

struct raw_connection
{
  bool handler;
  bool disconnected = false;
  mutex
    mutex_handler,
    mutex_received,
    mutex_send;

  list<raw_message> received;
  modules_container listeners;

  raw_connection(bool a)
    : handler(a) {}
};

struct connection
{
  shared_ptr<raw_connection> raw;


  operator bool() const;

  connection(bool);
  connection(const connection &);
  ~connection();

  bool exit_flag = false;
  future<void> receive_thread;
  void ReceiveThread();

  void Send(raw_message &);
};