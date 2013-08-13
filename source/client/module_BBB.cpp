#include "module_BBB.h"

enum
{
  MY_EVENT,
  AAA_TEST_EVENT,
};

module_BBB::module_BBB( ed::gateway &_gw ) : module("moduleBBB", _gw)
{
  RegisterEvent(TOSTRING(MY_EVENT), MY_EVENT);
  RegisterEvent("TEST_EVENT", AAA_TEST_EVENT);

  ed::event_source es;
  es.event = AAA_TEST_EVENT;
  RegisterPreHandler(&module_BBB::CheckAAAEventTEST, es);
}

#include <iostream>

bool module_BBB::CheckAAAEventTEST( const ed::event_context<> &c )
{
  std::cout << "MODULE_BBB PREEVENT " << c.event_local_id << " FROM " << c.source.instance << ":" << c.source.module << std::endl;
  return false;
}

void module_BBB::SendTestEvents()
{
  SendEvent(MY_EVENT);
}

module_BBB::~module_BBB()
{
  UnregisterHandlers(this);
}