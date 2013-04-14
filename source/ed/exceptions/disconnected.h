/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_EXCEPTIONS_EXCEPTION_H_
#define _ED_EXCEPTIONS_EXCEPTION_H_

#include "exception.h"

namespace ed
{
  struct diconnected : public exception
  {
  };
}

#endif