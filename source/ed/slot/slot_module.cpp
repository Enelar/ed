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

void module::RemoveDisconnected( const int instance )
{
  for (int i = 0; i < data.size(); i++)
    data[i].RemoveDisconnected(instance);
}

std::set<int> module::SubscribedInstances( const event_source &_es )
{
  std::set<int> ret, res1, res2;
  event_source es = _es;

  es.event = reserved::event::BROADCAST;
  try
  {
    event &e = GetEvent(_es);
    res1 = e.SubscribedInstances();
  } catch (slot_not_found )
  {
  }

  try
  {
    event &e = GetEvent(es);
    res2 = e.SubscribedInstances();
  } catch (slot_not_found )
  {
  }

  ret.insert(res1.begin(), res1.end());
  ret.insert(res2.begin(), res2.end());
  return ret;
}