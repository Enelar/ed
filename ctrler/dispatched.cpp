#include "dispatcher.h"
#include "ctrler.h"
#include <ed\structs\messages\simple_messages.h>
#include <iostream>

dispatcher::dispatcher(ctrler &that)
  : target(that)
{

}

void dispatcher::Translate(raw_message &gift)
{
  bool is_event_lookup = gift.event == ed::reserved::event::EVENT_NAME_LOOKUP;

  messages::_string message = gift;

  auto &book =
    is_event_lookup
    ? target.names.events
    : target.names.modules;

  cout << "translate " << is_event_lookup << " " << message.payload.str << endl;
  auto id = book.Add(message.payload.str);

  messages::_int ret;
  ret.Fill(gift);
  ret.Reverse();

  ret.payload.num = id;

  ret.event =
    is_event_lookup
    ? ed::reserved::event::EVENT_GLOBAL_ID_REQUEST
    : ed::reserved::event::MODULE_GLOBAL_ID_REQUEST;

  cout << "\tANSWER: " << id;
  target.Send(ret);
}

#include <ed\structs\messages\listen_message.h>
void dispatcher::Listen(raw_message &gift)
{
  messages::listen message = gift;

  cout << "listen: " 
    << message.payload.what << " from "
    << "("
    << message.payload.from.instance << ", "
    << message.payload.from.module
    << ")"
    << " to " << message.from.module;

    bool exceptional_fetch = message.payload.from.instance < ed::reserved::instance::FIRST_ALLOWED;

  if (exceptional_fetch && message.payload.from.instance != ed::reserved::instance::BROADCAST)
    throw "todo other";

  auto connection = target.connections.find(message.payload.from.instance);
  if (!exceptional_fetch && connection == target.connections.end())
    throw "connection not found";

  auto &module_container =
    exceptional_fetch
    ? target.exceptional_listen[message.payload.from.instance]
    : connection->second.raw->listeners;

  auto &listeners = module_container(message.payload.from.module)(message.payload.what);
  auto &listen_instance = listeners(message.from.instance);
  listen_instance.push_back(message.from.module);
}

void dispatcher::Transmit(raw_message &message)
{
  bool exceptional_fetch = message.from.instance < ed::reserved::instance::FIRST_ALLOWED;
  
  if (exceptional_fetch)
  {
    auto &exceptional_container = target.exceptional_listen[message.from.instance];
    TransmitHelper(exceptional_container, message);
  }
    
  auto connection = target.connections.find(message.from.instance);
  if (connection == target.connections.end())
    throw "connection not found"; // WTF???

  auto &module_container = connection->second.raw->listeners;
  TransmitHelper(module_container, message);
}

void dispatcher::TransmitHelper(modules_container &module_container, raw_message &message)
{
  auto &modules_holder = module_container;
  auto &events_holder = modules_holder[message.from.module];
  auto &listeners_holder = events_holder[message.event];
  if (!listeners_holder)
    return;


  auto &listeners = *listeners_holder;
  for (auto &listener_instance : listeners)
  {
    message.to.instance = listener_instance.first;
    for (auto listener_module : *listener_instance.second)
    {
      message.to.module = listener_module;
      target.Send(message);
    }
  }
}

void dispatcher::Up(raw_message &gift)
{
  if (gift.event == ed::reserved::event::MODULE_UP)
    cout << "MODULE " << gift.from.module << " UP";
  if (gift.event == ed::reserved::event::MODULE_DOWN)
    cout << "MODULE " << gift.from.module << " DOWN";

  Transmit(gift);
}