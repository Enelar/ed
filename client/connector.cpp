#define _ED_INTERNAL_CONNECTOR_NOCHECK_
#include "connector.h"
#include <ed/structs/messages/simple_messages.h>
#include <boost/lexical_cast.hpp>

connector::connector(boost::asio::io_service &_io)
  : io(_io), con(io)
{

}

void connector::Connect(string addr, int port)
{
  using namespace boost::asio::ip;

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
}

void connector::SendMessage(raw_message gift)
{
  gift.from.instance = global_instance_id;
  vector<byte> buf = gift;
  con.send(boost::asio::buffer(buf));
}

raw_message connector::WaitForMessage()
{
  vector<byte> buf;

  {
    const int sizeof_payload_size = 4;
    const int to_read = message_header::raw_byte_size + 4;
    buf.reserve(to_read); // size of payload
    boost::asio::read(con, boost::asio::buffer(buf, to_read));
    int payload_size = *(int *)(&buf[0] + message_header::raw_byte_size);
    if (payload_size > raw_message::max_message_size)
      throw "reading message is too big";
    buf.reserve(buf.size() + payload_size);
    boost::asio::read(con, boost::asio::buffer(&buf[0] + to_read, payload_size));
  }

  raw_message gift = &buf[0];
  if (gift.from.instance == ed::reserved::instance::CONTROLLER)
    if (gift.to.instance != ed::reserved::instance::BROADCAST)
      global_instance_id = gift.to.instance;
  return gift;
}

int connector::RegisterName(bool is_event, string name)
{
  {
    ::messages::_string request;
    request.to.instance = ed::reserved::instance::CONTROLLER;
    request.to.module = ed::reserved::module::BROADCAST;
    request.from.module = ed::reserved::module::BROADCAST;
    if (is_event)
      request.event = ed::reserved::event::EVENT_NAME_LOOKUP;
    else
      request.event = ed::reserved::event::MODULE_NAME_LOOKUP;

    request.payload.str = name;
    SendMessage(request);
  }

  ::messages::_int response = WaitForMessage();
  int global_id = response.payload.num;

  if (is_event)
    names.events.Insert(global_id, name);
  else
    names.modules.Insert(global_id, name);

  return global_id;
}