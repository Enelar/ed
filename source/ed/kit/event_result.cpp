/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#include "event_result.h"

using namespace ed;

event_result::event_result( module &_m, int _local_id, bool _result )
  : m(_m), local_id(_local_id), result(_result), deactivated(false)
{
}

event_result::event_result( const event_result &a )
  : m(a.m), local_id(a.local_id), result(a.result), deactivated(false)
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
    m.SendPostEvent(local_id);
}