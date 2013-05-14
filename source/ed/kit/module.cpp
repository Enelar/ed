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

bool module::SendPreEvent( int local_id, buffer payload )
{
  return gw.PreNotify(adapter.ToGlobal(local_id), id, payload);
}

void module::SendPostEvent( int local_id, buffer payload )
{
  gw.PostNotify(adapter.ToGlobal(local_id), id, payload);
}


bool module::SendPreEvent( int local_id )
{
  return gw.PreNotify(adapter.ToGlobal(local_id), id, buffer(0));
}

void module::SendPostEvent( int local_id )
{
  gw.PostNotify(adapter.ToGlobal(local_id), id, buffer(0));
}