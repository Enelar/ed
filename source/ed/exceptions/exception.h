#ifndef _ED_EXCEPTIONS_EXCEPTION_H_
#define _ED_EXCEPTIONS_EXCEPTION_H_

#include "../def.h"
#include <string>
#include <ostream>

namespace ed
{
  struct exception;
};
__declspec(dllexport) std::ostream & operator<<( std::ostream &os, const ed::exception &e );
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
    friend std::ostream & ::operator<<( std::ostream &, const exception & );
  };
}

#ifdef _SLOW_THROW_
  #define EXCEPTION(x) throw x
#else
  #define EXCEPTION(x) throw NEW x
#endif

#if _DEBUG_
  #define THROW(exception, message) EXCEPTION(exception(__FILE__, __LINE__, message))
#else
  #define THROW(exception, message) EXCEPTION(exception(__FILE__, __LINE__))
#endif

#define throw_force_message(string) EXCEPTION(ed::exception(__FILE__, __LINE__, string))

#define throw_message(string) THROW(ed::exception, string)

#define throw_sassert(cond, string) if (!(cond)) throw_message("ASSERTION FAULT {" string "}"); else

#define throw_assert(cond) throw_sassert(cond, TOSTRING(cond))

#if _DEBUG_
#define todo(ToDoMessage) throw_force_message("TODO: " TOSTRING(ToDoMessage))
#else
#define todo(ToDoMessage) throw_force_message("This function coming soon. (TODO)")
#endif

#define dead_space() throw_message("Unexpected routeline")
#define do_overload(func_with_full_namespace_address) throw_message("Overload not completed: " func_with_full_namespace_address);

#endif