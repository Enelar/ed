/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#include "slot_data_utils.h"
#include "instance.h"

using namespace ed::slot_data;


void SearchEvent::Direct( ed::slot_data::module &m)
{
  int id = targets[2];
  throw_assert(id >= 0);
  throw_assert(id < m.childs.size());
  e = &m.childs[id];
}