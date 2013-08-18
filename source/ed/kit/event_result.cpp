#include "event_result.h"

using namespace ed;

event_result::event_result( message &_e, module_base &_m, int _local_id, bool _result, EVENT_RING _notify )
  : m(_m), local_id(_local_id), result(_result), deactivated(false),
  e(_e), r(_notify)
{
}

event_result::event_result( const event_result &a )
  : m(a.m), local_id(a.local_id), result(a.result), deactivated(false), e(a.e), r(a.r)
{
  a.deactivated = true;
}

event_result::operator bool &()
{
  return result;
}

event_result::operator bool() const
{
  return result;
}

event_result::~event_result()
{
  if (!deactivated)
  {
    if (result)
      e.flags.state = POST_COMMIT;
    else
     e.flags.state = POST_CANCEL;
    e.flags.ring = r;
    m.SendPostEvent(local_id, e);
  }
}