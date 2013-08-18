#include "event.h"

using namespace ed::slot;
using namespace ed;

void event::AddListener( const listen_message &m, bool force )
{
  AddListener((slot_data::listener)m);
}

void event::AddListener( const slot_data::listener &m, bool force )
{
  if (ListenerExist(m))
    return;
  data.push_back(m);
}

bool event::ListenerExist( const slot_data::listener &m ) const
{
  for (int i = 0, s = data.size(); i < s; i++)
    if (data[i] == m)
      return true;
  return false;
}

void event::RemoveDisconnected( const int instance )
{
  std::vector<slot_data::listener>::const_iterator i = data.begin(), e = data.end();

  while (i != e)
    if ((*i).instance == instance)
    {
      i = data.erase(i);
      e = data.end();
    }
    else
      i++;
}

std::set<int> event::Subscribed( int slot_data::listener::* type ) const
{
  std::set<int> ret;
  std::vector<slot_data::listener>::const_iterator i = data.begin(), e = data.end();

  while (i != e)
  {
    ret.insert((*i).*type);
    i++;
  }
  return ret;
}