/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_EXCEPTIONS_EXCEPTION_H_
#define _ED_EXCEPTIONS_EXCEPTION_H_

#include "../def.h"
#include <string>

namespace ed
{
  struct exception
  {
    typedef std::string string;
    const string file, comment;
    const int line;
    exception( const string _file, const int _line, const string _comment ) :
      file(_file), line(_line), comment(_comment)
    {
    }
    exception( const string _file, const int _line ) :
      file(_file), line(_line), comment("")
    {
    }
  };
}

#ifdef _SLOW_THROW_
  #define EXCEPTION(x) throw x
#else
  #define EXCEPTION(x) throw NEW x
#endif

#if _DEBUG_
  #define throw_message(string) EXCEPTION(ed::exception(__FILE__, __LINE__, string))
#else
  #define throw_message(string) EXCEPTION(ed::exception(__FILE__, __LINE__))
#endif

#define throw_sassert(cond, string) if (!(cond)) throw_message("ASSERTION FAULT {" string "}"); else

#define throw_assert(cond) throw_sassert(cond, TOSTRING(cond))

#endif