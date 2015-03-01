#include "example_module.h"
#include <ed/structs/messages/simple_messages.h>

enum EVENTS
{
  EVENT_AAA,
  EVENT_BBB
};

string event_names[] =
{
  "EVENT_AAA",
  "EVENT_BBB",
};

int module_id = -1;


int example_module::GetNameID(bool is_event, string name)
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
    Send(request);
  }

  messages::_int response = WaitForMessage();

  if (is_event)
    names.events.Insert(response.payload.num, name);

  
}

void example_module::Send(const raw_message &)
{

}

void example_module::Subscribe()
{
  names.events.Insert(EVENT_AAA, "EVENT_AAA");
  names.events.Insert(EVENT_BBB, "EVENT_BBB");
  names.modules.Insert(1, "MODULE");
}

void example_module::Emit()
{

}