#include "connector.h"
#include <ed/structs/messages/simple_messages.h>

static connector singletone_connector;

void connector::SendMessage(const raw_message &)
{

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