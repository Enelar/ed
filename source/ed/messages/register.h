/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_MESSAGES_REGISTER_H_
#define _ED_MESSAGES_REGISTER_H_

#include "../names/name_type.h"
#include "message.h"

namespace ed
{
  struct register_message
  {
    NAME_TYPE nt;
    std::string name;

    register_message( message &e )
    {
      throw_assert(e.GetType() == REGISTER);
      todo("Parse register message");
    }
    
    register_message( NAME_TYPE _nt, std::string _name )
      : nt(_nt), name(_name)
    {
    }
    
    operator message() const
    {
      todo("Convert to message");
    }
  };
};

#endif