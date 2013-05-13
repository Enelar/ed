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
      throw_assert(e.len > 2);
      nt = (NAME_TYPE)e.buffer[1];
      int len = e.buffer[2];
      char *buf = NEW char[len + 1];
      memcpy(buf, e.buffer + 3, len);
      buf[len] = 0;
      name = buf;
      delete buf;
    }
    
    register_message( NAME_TYPE _nt, std::string _name )
      : nt(_nt), name(_name)
    {
    }
    
    operator message() const
    {
      message ret(name.length() + 3);
      ret.buffer[0] = REGISTER;
      ret.buffer[1] = nt;
      ret.buffer[2] = name.length();
      memcpy(ret.buffer + 3, name.c_str(), name.length());
      return ret;
    }
  };
};

#endif