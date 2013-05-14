#ifndef _ED_KIT_GATEWAY_H_
#define _ED_KIT_GATEWAY_H_

#include <string>
#include "../communications/abstract_connection.h"
#include "../names/translate.h"

namespace ed
{
  class module;
  class gateway
  {
    com::abstract_connection &c;
    friend class module;
    int RegisterEvent( std::string name );
    bool PreNotify( int local_id, int module, buffer payload );
    void PostNotify( int local_id, int module, buffer payload );
    int instance;
  public:
    gateway( com::abstract_connection & );
    module &CreateModule( std::string name );
  };
};

#include "module.h"

#endif