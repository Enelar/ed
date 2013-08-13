#include "instance.h"

using namespace ed::slot;
using namespace ed;

com::abstract_connection &instance::Socket() const
{
  return *con;
}

module &instance::GetModule( const int i )
{
  if (i < 0 || i >= data.size())
    throw slot_not_found();
  return data[i];
}

module &instance::GetModule( const event_source &es )
{
  return GetModule(es.module);
}

event &instance::GetEvent( const event_source &es )
{
  return GetModule(es).GetEvent(es);
}

void instance::AddListener( const listen_message &m )
{
  GetModule(m).AddListener(m);
}