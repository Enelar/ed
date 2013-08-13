#include "instance.h"

using namespace ed::slot;
using namespace ed;

com::abstract_connection &instance::Socket() const
{
  return *con;
}

module &instance::GetModule( const int i, bool force )
{
  if (i < 0 || i >= data.size())
    if (force)
      Create(i);
    else
      throw slot_not_found();
  return data[i];
}

module &instance::GetModule( const event_source &es, bool force )
{
  return GetModule(es.module, force);
}

event &instance::GetEvent( const event_source &es, bool force )
{
  return GetModule(es, force).GetEvent(es, force);
}

void instance::Create( int i )
{
  while (data.size() < i)
    data.push_back(module());
}

void instance::AddListener( const listen_message &m, bool force )
{
  GetModule(m, force).AddListener(m, force);
}