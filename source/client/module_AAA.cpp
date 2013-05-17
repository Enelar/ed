#include "module_AAA.h"

enum MY_EVENTS
{
  TEST_EVENT
};

module_AAA::module_AAA( ed::gateway &_gw ) : module("module_AAA", _gw)
{
  RegisterEvent(TOSTRING(TEST_EVENT), TEST_EVENT);
  ed::event_source es;
  es.event = TEST_EVENT;
  RegisterEventCallback(static_cast<event_callback_type>(&module_AAA::AllEventsListener), es);
}

#include <iostream>

void module_AAA::AllEventsListener( const event_context &c )
{
  std::cout << "MODULE_AAA RECIEVED EVENT " << c.event_local_id << " FROM " << c.source.instance << ":" << c.source.module << std::endl;
}

void module_AAA::SendTestEvents()
{
  SendEvent(TEST_EVENT);
}