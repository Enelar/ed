#ifndef _ED_MESSAGES_REGISTER_H_
#define _ED_MESSAGES_REGISTER_H_

#include "../names/name_type.h"
#include "message.h"

namespace ed
{
  struct _ED_DLL_EXPORT_ register_message
  {
    NAME_TYPE nt;
    std::string &name;

    register_message( message &e );
    
    register_message( NAME_TYPE _nt, std::string _name )
      : nt(_nt), name(*NEW std::string(_name))
    {
    }

    ~register_message()
    {
      delete &name;
    }
    
    operator message() const;
  };
};

#endif