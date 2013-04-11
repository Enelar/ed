/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NAME_SERVER_H_
#define _ED_NAME_SERVER_H_

#include "name_type.h"
#include "dictionary.h"

namespace ed
{
  struct name_server
  {
    dictionary books[COUNT];
    void ValidateBookId( const NAME_TYPE nt ) const;
  public:
    dictionary &operator[]( const NAME_TYPE nt );
    const dictionary &operator[]( const NAME_TYPE nt ) const;
  };
};

#endif