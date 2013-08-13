#include "module.h"

using namespace ed::slot;
using namespace ed;

event &module::GetEvent( const int i, bool force )
{
  if (i < 0 || i >= data.size())
    if (force)
      Create(i);
    else
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

void module::Create( int i )
{
  while (data.size() <= i)
    data.push_back(event());
}