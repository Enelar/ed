#include "slot_data_utils.h"
#include "instance.h"

using namespace ed::slot_data;


void SearchEvent::Direct( ed::slot_data::module &m)
{
  unsigned int id = targets[2];
  throw_assert(id >= 0);
  throw_assert(id < m.childs.size());
  e = &m.childs[id];
}

void SearchEvent::IfExists( module & m )
{
  unsigned int id = targets[2];
  e = NULL;
  if (id < 0 || id >= m.childs.size())
    return;
  e = &m.childs[id];
}