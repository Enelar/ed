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
  RegisterQueryCallback(static_cast<query_callback_type>(&module_BBB::CheckAAAEventTEST), es);
}

bool module_BBB::CheckAAAEventTEST( const event_context & )
{
  return false;
}

void module_BBB::SendTestEvents()
{
  SendEvent(MY_EVENT);
}