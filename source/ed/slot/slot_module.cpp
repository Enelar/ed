#include "module.h"

using namespace ed::slot;
using namespace ed;

event &module::GetEvent( const int i, bool force )
{
  if (i < 0 || i >= data.size())
    throw slot_not_found();
  return data[i];
}

event &module::GetEvent( const event_source &es, bool force )
{
  return GetEvent(es.event, force);
}

void module::AddListener( const listen_message &m, bool force )
{
  GetEvent(m, force).AddListener(m, force);
}