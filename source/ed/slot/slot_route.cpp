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

module &route::GetModule( const event_source &es, bool force )
{
  return GetInstance(es).GetModule(es, force);
}

event &route::GetEvent( const event_source &es, bool force )
{
  return GetInstance(es).GetEvent(es, force);
}

void route::AddListener( const listen_message &m, bool force )
{
  GetInstance(m).AddListener(m, force);
}

void route::AddListener( const event_source &es, const slot_data::listener &li, bool force )
{
  GetEvent(es, force).AddListener(li, force);
}

int route::AddInstance( com::abstract_connection *a )
{
  int ret = data.size();
  data.push_back(instance());
  data[ret].con = a; // crapcode
  return ret;
}