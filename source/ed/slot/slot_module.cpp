#include "module.h"

using namespace ed::slot;
using namespace ed;

event &module::GetEvent( const int i )
{
  if (i < 0 || i >= data.size())
    throw slot_not_found();
  return data[i];
}

event &module::GetEvent( const event_source &es )
{
  return GetEvent(es.event);
}

void module::AddListener( const listen_message &m )
{
  GetEvent(m).AddListener(m);
}