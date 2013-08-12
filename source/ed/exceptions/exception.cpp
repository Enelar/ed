#include "exception.h"

std::ostream &operator<<( std::ostream &os, const ed::exception &e )
{
  if (e.comment->length() != 0)
    os << "`" << *e.comment << "`, ";
  os << "ed::exception throwed at " << *e.file << ":" << e.line;
  return os;
}
