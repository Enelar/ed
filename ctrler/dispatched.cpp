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

  cout << "translate " 
    << (is_event_lookup ? "event" : "module")
    << " " << message.payload.str << endl;
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
#include <boost/lexical_cast.hpp>
void dispatcher::Listen(raw_message &gift)
{
  ::messages::listen message = gift;

  string instance;
  {
    using namespace ed::reserved::instance;
    auto it = _strings.find(message.payload.from.instance);
    if (it != _strings.end())
      instance = it->second;
    else
      instance == boost::lexical_cast<string>(message.payload.from.instance);
  }

  cout << "listen: "
    << ed::reserved::event::DebugStrings(target.names.events)[message.payload.what] << " from "
    << instance << "->"
    << ed::reserved::event::DebugStrings(target.names.modules)[message.payload.from.module]
    << " to " << ed::reserved::event::DebugStrings(target.names.modules)[message.from.module]
    << endl;
  cout << "\tOK";

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
  bool exceptional_fetch = message.to.instance < ed::reserved::instance::FIRST_ALLOWED;

  if (exceptional_fetch)
  {
    auto &exceptional_container = target.exceptional_listen[message.to.instance];
    TransmitHelper(exceptional_container, message, true);
    TransmitHelper(exceptional_container, message);
    return;
  }

  auto connection = target.connections.find(message.to.instance);
  if (connection == target.connections.end())
    throw "connection not found"; // WTF???

  auto &module_container = connection->second.raw->listeners;
  TransmitHelper(module_container, message, true);
  TransmitHelper(module_container, message);
}

void dispatcher::TransmitHelper(modules_container &module_container, raw_message &message, bool broadcast)
{
  auto &modules_holder = module_container;
  auto &events_holder = modules_holder[!broadcast ? message.from.module : ed::reserved::module::BROADCAST];
  auto &listeners_holder = events_holder[message.event];
  if (!listeners_holder)
    return;


  auto &listeners = *listeners_holder;
  for (auto listener_instance : listeners)
  {
    message.to.instance = listener_instance.first;
#ifndef _DEBUG
    if (message.to.instance == message.from.instance)
      continue; // you cant emit to yourself through ctrler. do it localy.
#endif
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
    cout << ed::reserved::module::DebugStrings(target.names.modules)[gift.from.module] << " UP" << endl;
  if (gift.event == ed::reserved::event::MODULE_DOWN)
    cout << ed::reserved::module::DebugStrings(target.names.modules)[gift.from.module] << " DOWN" << endl;
  cout << "\tOK";

  Transmit(gift);
}