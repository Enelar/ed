#include "module_AAA.h"

enum MY_EVENTS
{
  TEST_EVENT
};

module_AAA::module_AAA( ed::gateway &_gw ) : module("module_AAA", _gw)
{
  RegisterEvent(TOSTRING(TEST_EVENT), TEST_EVENT);
  RegisterEventCallback(static_cast<event_callback_type>(&module_AAA::AllEventsListener), ed::event_source());
}

void module_AAA::AllEventsListener( const event_context & )
{
  
}

void module_AAA::SendTestEvents()
{
  SendEvent(TEST_EVENT);
}