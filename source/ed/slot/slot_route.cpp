#include "route.h"

using namespace ed::slot;
using namespace ed;


instance &route::GetInstance( const int i )
{
  if (i < 0 || i >= data.size())
    throw slot_not_found();
  return data[i];
}

instance &route::GetInstance( const event_source &es )
{
  return GetInstance(es.instance);
}

module &route::GetModule( const event_source &es )
{
  return GetInstance(es).GetModule(es);
}

event &route::GetEvent( const event_source &es )
{
  return GetInstance(es).GetEvent(es);
}

void route::AddListener( const listen_message &m )
{
  GetInstance(m).AddListener(m);
}

void route::AddListener( const event_source &es, const slot_data::listener &li )
{
  GetEvent(es).AddListener(li);
}

int route::AddInstance( com::abstract_connection *a )
{
  int ret = data.size();
  data.push_back(instance());
  data[ret].con = a; // crapcode
  return ret;
}