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
  SysCreateHandler(&module_AAA::AllEventsListener, es);
 // SetPostEventHandler(static_cast<post_event_handler_t>(&module_AAA::AllEventsListener), es);
//  SetPostEventHandler(&module_AAA::MyTypeExample, es);
}

void module_AAA::MyTypeExample( const ed::event_context<my_type> &a )
{

}

#include <iostream>

void module_AAA::AllEventsListener( const ed::event_context<> &c )
{
  std::cout << "MODULE_AAA RECIEVED EVENT " << c.event_local_id << " FROM " << c.source.instance << ":" << c.source.module << std::endl;
}

void module_AAA::SendTestEvents()
{
  SendEvent(TEST_EVENT);
}