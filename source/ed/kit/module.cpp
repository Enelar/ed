#include "module.h"

using namespace ed;

module::module( int _id, gateway &_gw )
  : id(_id), gw(_gw)
{
}

void module::RegisterEvent( std::string name, int local_id )
{
  int global_id = gw.RegisterEvent(name);
  adapter.AddPair(local_id, global_id);
}

event_result module::SendEvent( int local_id )
{
  bool result = SendPreEvent(local_id);
  return event_result(*this, local_id, result);
}

bool module::SendPreEvent( int local_id )
{
  todo(Send PRE_CHANGE events);
  todo(Send PRE_LISTEN events);
  todo(Recieve PRE_CHANGE events result);
  todo(SendPreEvent);
}

void module::SendPostEvent( int local_id )
{
  todo(SendPostEvent);
}