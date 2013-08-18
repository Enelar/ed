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

void route::RemoveDisconnected( const int instance )
{
  for (int i = 0; i < data.size(); i++)
    data[i].RemoveDisconnected(instance);
  delete GetInstance(instance).con;
  GetInstance(instance).con = NULL;
}

std::set<int> route::SubscribedInstances( const event_source &_es )
{
  std::set<int> ret, res1, res2;
  event_source es = _es;

  es.instance = reserved::instance::BROADCAST;
  try
  {
    instance &e = GetInstance(_es);
    res1 = e.SubscribedInstances(_es);
  } catch (slot_not_found )
  {
  }

  try
  {
    instance &e = GetInstance(es);
    res2 = e.SubscribedInstances(_es);
  } catch (slot_not_found )
  {
  }

  ret.insert(res1.begin(), res1.end());
  ret.insert(res2.begin(), res2.end());
  return ret;
}