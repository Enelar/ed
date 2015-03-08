#define _ED_INTERNAL_CONNECTOR_NOCHECK_
#include "connector.h"
#include <ed/structs/messages/simple_messages.h>
#include <ed/structs/messages/handshake.h>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <thread>

connector::connector(boost::asio::io_service &_io)
  : io(_io), con(io)
{

}

void connector::Connect(string addr, int port)
{
  using namespace boost::asio::ip;
  target.determined = true;
  target.addr = addr;
  target.port = port;

  tcp::resolver resolver(io);
  tcp::resolver::query query(addr, boost::lexical_cast<string>(port));
  tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
  tcp::resolver::iterator end;

  boost::system::error_code error = boost::asio::error::host_not_found;
  while (error && endpoint_iterator != end)
  {
    con.close();
    con.connect(*endpoint_iterator++, error);
  }
  if (error)
    throw boost::system::system_error(error);

  {
    ::messages::handshake gift;
    Send(gift);
  }

  {
    ::messages::handshake gift = WaitForMessage();
    int server_protocol_version = gift.payload.version;
    if (server_protocol_version != ed::reserved::protocol_version)
      throw "Protocols should be equal. Sorry, im still in development.";
    global_instance_id = gift.to.instance;
  }

  cout << "Handshake succeed! My id is " << global_instance_id << endl;
}

void connector::Send(raw_message gift)
{
  if (!target.determined)
    throw "connect to controller first!";
  gift.from.instance = global_instance_id;
  vector<byte> buf = gift;
  con.send(boost::asio::buffer(buf));
}

raw_message connector::WaitForMessage()
{
  vector<byte> buf;

  cout << "Wait for message..." << endl;
  {
    const int sizeof_payload_size = 4;
    const int to_read = message_header::raw_byte_size + 4;
    buf.resize(to_read); // size of payload
    while (con.available() < to_read)
      this_thread::sleep_for(10ms);
    boost::asio::read(con, boost::asio::buffer(buf, to_read));
    int payload_size = *(int *)(&buf[0] + message_header::raw_byte_size);
    if (payload_size > raw_message::max_message_size)
      throw "reading message is too big";
    while (con.available() < payload_size)
      this_thread::sleep_for(10ms);
    buf.reserve(buf.size() + payload_size);
    boost::asio::read(con, boost::asio::buffer(&buf[0] + to_read, payload_size));
  }
  cout << "Get message..." << endl;

  return{ &buf[0] };
}

int connector::RegisterName(bool is_event, string name)
{
  {
    ::messages::_string request;
    request.to.instance = ed::reserved::instance::CONTROLLER;
    request.to.module = ed::reserved::module::NAMES;
    request.from.module = ed::reserved::module::NAMES;
    if (is_event)
      request.event = ed::reserved::event::EVENT_NAME_LOOKUP;
    else
      request.event = ed::reserved::event::MODULE_NAME_LOOKUP;

    request.payload.str = name;
    Send(request);
  }

  ::messages::_int response = WaitForMessage();
  int global_id = response.payload.num;

  if (is_event)
    names.events.Insert(global_id, name);
  else
    names.modules.Insert(global_id, name);

  return global_id;
}

#include <ed/structs/messages/listen_message.h>
void connector::Listen(int event, int module, message_destination from)
{
  auto it = listeners.find(event);
  if (it == listeners.end())
  {
    listeners.insert({ event, boost::container::flat_set<int>() });
    it = listeners.find(event);
    if (it == listeners.end())
      throw "WTF";
  }
  auto &set = it->second;
  if (set.find(module) != set.end())
    return; // already registered
  set.insert(module);

  ::messages::listen gift;
  gift.payload.what = event;
  gift.payload.from = from;
  gift.from.module = module;
  gift.event = ed::reserved::event::LISTEN;
  gift.to.instance = ed::reserved::instance::CONTROLLER;
  gift.to.module = ed::reserved::module::LISTEN;

  Send(gift);
}