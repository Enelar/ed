/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#include "name_server.h"
#include "../exceptions/exception.h"
#include "reserved.h"

using namespace ed;

#define REGISTER_WORD(obj, word)         \
throw_assert(                            \
  word ==                                \
    (                                    \
      (obj).RegisterWord(                \
                    TOSTRING(word)       \
                        )                \
    )                                    \
            )

#include <iostream>
#include <sstream>

namespace
{
  template<class type>
  std::string string_cast( const type & );

  template<>
  std::string string_cast<int>( const int &a )
  {
    std::stringstream ss;
    ss << a;
    return ss.str();
  }
  
  void Reserve( dictionary &e, int id )
  {
    std::string s = "RESERVED_";
    s += string_cast<>(id);
    throw_assert(e.RegisterWord(s) == id);
  }
  
  void Reserve( dictionary &e, int min, int max )
  {
    for (int i = min; i <= max; ++i)
      Reserve(e, i);
  }
};

name_server::name_server()
{
  dictionary &a = (*this)[INSTANCES];
  {
    using namespace ed::reserved::instance;
    REGISTER_WORD(a, BROADCAST);
    REGISTER_WORD(a, MASTER);
    REGISTER_WORD(a, CONTROLLER);
    Reserve(a, CONTROLLER + 1, FIRST_ALLOWED - 1);
  }
  
  a = (*this)[MODULES];
  {
    using namespace ed::reserved::module;
    REGISTER_WORD(a, BROADCAST);
    REGISTER_WORD(a, HEART_BEAT);
    Reserve(a, HEART_BEAT + 1, FIRST_ALLOWED - 1);
  }

  a = (*this)[EVENTS];
  {
    using namespace ed::reserved::event;
    REGISTER_WORD(a, BROADCAST);
    REGISTER_WORD(a, INSTANCE_UP);
    REGISTER_WORD(a, MODULE_UP);
    REGISTER_WORD(a, EVENT_REGISTER);
    REGISTER_WORD(a, LISTEN);
    Reserve(a, RESERVED_5);
    REGISTER_WORD(a, MODULE_NAME_LOOKUP);
    REGISTER_WORD(a, EVENT_NAME_LOOKUP );
    REGISTER_WORD(a, MODULE_GLOBAL_ID_REQUEST);
    REGISTER_WORD(a, EVENT_GLOBAL_ID_REQUEST);
    Reserve(a, EVENT_GLOBAL_ID_REQUEST + 1, FIRST_ALLOWED - 1);
  }
}

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
