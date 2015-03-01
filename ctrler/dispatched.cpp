#include "dispatcher.h"
#include "ctrler.h"
#include "messages\simple_messages.h"

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
  
  auto id = book.Add(message.payload.str);

  messages::_int ret;
  ret.Fill(gift);
  
  ret.payload.num = id;

  ret.event =
    is_event_lookup
    ? ed::reserved::event::EVENT_GLOBAL_ID_REQUEST
    : ed::reserved::event::MODULE_GLOBAL_ID_REQUEST;
  
  ret.Reverse();

  target.Send(ret);
}

#include "messages\listen_message.h"
void dispatcher::Listen(raw_message &gift)
{
  messages::listen message = gift;

  bool exceptional_fetch = message.from.instance < ed::reserved::instance::FIRST_ALLOWED;
  
  if (exceptional_fetch && message.from.instance != ed::reserved::instance::BROADCAST)
    throw "todo other";

  auto connection = target.connections.find(message.payload.from.instance);
  if (!exceptional_fetch && connection == target.connections.end())
    throw "connection not found";

  auto &module_container =
    exceptional_fetch
        ? target.exceptional_listen[message.payload.from.instance]
        : connection->second.raw->listeners;

  auto &modules = module_container;
  auto &events = modules[message.from.module];
 // auto &listeners = events[message.payload.what];
  //auto listeners = [message.payload.what];
}

void dispatcher::Up(raw_message &)
{

}