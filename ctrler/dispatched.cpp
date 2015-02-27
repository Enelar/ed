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

  messages::_string message(gift);

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

void dispatcher::Listen(raw_message &)
{

}

void dispatcher::Up(raw_message &)
{

}