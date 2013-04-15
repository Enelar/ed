/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */


#include "exception.h"

std::ostream &operator<<( std::ostream &os, const ed::exception &e )
{
  if (e.comment.length() != 0)
    os << "`" << e.comment << "`, ";
  os << "ed::exception throwed at " << e.file << ":" << e.line;
  return os;
}
