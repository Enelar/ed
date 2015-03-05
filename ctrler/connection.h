#pragma once

#include <future>
#include <memory>
#include <mutex>
#include <list>
using namespace std;

#include <ed\structs\message.h>
#include "containers.h"
#include <boost\asio.hpp>

struct raw_connection
{
  typedef boost::asio::ip::tcp::socket handlerT;
  unique_ptr<handlerT> handler;
  bool
    disconnected = false,
    handshake_required = true;
  mutex
    mutex_handler,
    mutex_received,
    mutex_send;

  list<raw_message> received;
  modules_container listeners;

  raw_connection(handlerT *a)
    : handler(a) {}
};

struct connection
{
  shared_ptr<raw_connection> raw;


  operator bool() const;

  connection(raw_connection::handlerT *);
  connection(const connection &);
  ~connection();

  bool exit_flag = false;
  future<void> receive_thread;
  void ReceiveThread();

  void Send(raw_message &);
};