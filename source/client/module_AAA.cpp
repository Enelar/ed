#include "module_AAA.h"

module_AAA::module_AAA( ed::gateway _gw ) : module("module_AAA", _gw)
{
  RegisterEventCallback(static_cast<event_callback_type>(&module_AAA::AllEventsListener), ed::event_source());
}

void module_AAA::AllEventsListener( const event_context & )
{
  
}