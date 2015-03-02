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

example_module::example_module()
  : module("MODULE")
{

}

void example_module::Subscribe()
{
  RegisterEventName("EVENT_AAA", EVENT_AAA);
  RegisterEventName("EVENT_BBB", EVENT_BBB);
}