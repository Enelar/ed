#pragma once

#include <ed/structs/message.h>
#include <ed/structs/library.h>

#include <boost/asio.hpp>
#include <boost/container/flat_set.hpp>

class connector
{
  int global_instance_id = ed::reserved::instance::BROADCAST;
  library names; // strings to global ids

  struct
  {
    bool determined = false;
    string addr;
    int port;
  } target;

  boost::asio::ip::tcp::socket con;
  boost::asio::io_service &io;
public:
  connector(boost::asio::io_service &);
  void Connect(string addr, int port);

  void Send(raw_message);
  raw_message WaitForMessage();

  int RegisterName(bool is_event, string name);
  void Listen(
    int which_event,
    int handle_module,
    message_destination from = { ed::reserved::instance::BROADCAST, ed::reserved::module::BROADCAST });

private:
  // event -> sorted vector of modules
  unordered_map<int, boost::container::flat_set<int>> listeners;
  friend class module;

  unordered_map<int, module *> modules;
  void RegisterModule(int global_id, module *);
  void UnregisterModule(int global_id);
};

extern connector singletone_connector;

#ifndef _ED_INTERNAL_CONNECTOR_NOCHECK_
#ifndef _ED_CONNECTOR_DEFINED_
#error You should define global connector in one of yours cpp files. Or you will get link error. If you understand this, define _ED_CONNECTOR_DEFINED_
#endif
#endif

