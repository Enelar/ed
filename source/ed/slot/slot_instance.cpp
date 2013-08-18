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
  while (data.size() <= i)
    data.push_back(module());
}

void instance::AddListener( const listen_message &m, bool force )
{
  GetModule(m, force).AddListener(m, force);
}

void instance::RemoveDisconnected( const int instance )
{
  for (int i = 0; i < data.size(); i++)
    data[i].RemoveDisconnected(instance);
}

std::set<int> instance::Subscribed( int slot_data::listener::* type, const event_source &_es )
{
  std::set<int> ret, res1, res2;
  event_source es = _es;

  es.module = reserved::module::BROADCAST;
  try
  {
    module &e = GetModule(_es);
    res1 = e.Subscribed(type, _es);
  } catch (slot_not_found )
  {
  }

  try
  {
    module &e = GetModule(es);
    res2 = e.Subscribed(type, _es);
  } catch (slot_not_found )
  {
  }

  ret.insert(res1.begin(), res1.end());
  ret.insert(res2.begin(), res2.end());
  return ret;
}