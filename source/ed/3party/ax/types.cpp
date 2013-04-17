/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Develop Project agreement
 * No part of this file could be used or viewed without Develop Project agreement
 */

#include "types.h"
#include "../../exceptions/exception.h"

using namespace ax;

shared::shared() : users(0)
{
}
void shared::AddShare( )
{
  ++users;
}
void shared::RemoveShare( )
{
  throw_assert(users);
  --users;
}
shared::~shared()
{
  throw_assert(!users);
}
void shared_self_controlled::RemoveShare( )
{
  shared::RemoveShare();
  if (!users)
    delete this;
}