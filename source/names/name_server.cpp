/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#include "name_server.h"
#include "exceptions/exception.h"

using namespace ed;

void name_server::ValidateBookId( const NAME_TYPE nt ) const
{
  throw_assert(nt >= 0);
  throw_assert(nt < COUNT);
}

dictionary &name_server::operator[]( const NAME_TYPE nt )
{
  ValidateBookId(nt);
  return books[nt];
}

const dictionary &name_server::operator[]( const NAME_TYPE nt ) const
{
  ValidateBookId(nt);
  return books[nt];
}
