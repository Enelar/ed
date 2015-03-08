#include "example_module.h"
#include <ed/structs/messages/simple_messages.h>
#include <iostream>

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

example_module::example_module()
  : module("MODULE")
{

}

void example_module::Subscribe()
{
  RegisterEventName("EVENT_AAA", EVENT_AAA);
  RegisterEventName("EVENT_BBB", EVENT_BBB);

  Listen(&example_module::ExampleHandler, EVENT_AAA);
}

void example_module::Emit()
{
  module::Emit(EVENT_AAA, MyLocation().module);
}

void example_module::ExampleHandler(raw_message rm)
{
  std::cout << "Message appeared" << rm.event;
}