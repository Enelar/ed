/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#include "module.h"

using namespace ed;

module::module( int _id, gateway &_gw )
  : id(_id), gw(_gw)
{
}

void module::RegisterEvent( std::string name, int local_id )
{
  int global_id = gw.RegisterEvent(name);
  adapter.AddPair(local_id, global_id);
}