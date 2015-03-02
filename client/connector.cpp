#define _ED_INTERNAL_CONNECTOR_NOCHECK_
#include "connector.h"
#include <ed/structs/messages/simple_messages.h>

connector::connector(boost::asio::io_service &_io)
  : io(_io), con(io)
{

}

void connector::Connect(string addr, int port)
{

}

void connector::SendMessage(raw_message gift)
{
  gift.from.instance = global_instance_id;
  // TODO: Boost send messages
}

raw_message connector::WaitForMessage()
{
  // TODO: Boost recieve message
  raw_message gift;
  if (gift.from.instance == ed::reserved::instance::CONTROLLER)
    if (gift.to.instance != ed::reserved::instance::BROADCAST)
      global_instance_id = gift.to.instance;
  return gift;
}

int connector::RegisterName(bool is_event, string name)
{
  {
    messages::_string request;
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

  messages::_int response = WaitForMessage();
  int global_id = response.payload.num;

  if (is_event)
    names.events.Insert(global_id, name);
  else
    names.modules.Insert(global_id, name);

  return global_id;
}