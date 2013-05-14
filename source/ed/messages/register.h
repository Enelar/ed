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
      todo(register message);
    }
    
    register_message( NAME_TYPE _nt, std::string _name )
      : nt(_nt), name(_name)
    {
    }
    
    operator message() const;
  };
};

#endif