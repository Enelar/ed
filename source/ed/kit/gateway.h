#ifndef _ED_KIT_GATEWAY_H_
#define _ED_KIT_GATEWAY_H_

#include <list>
#include <vector>
#include <string>
#include "../communications/abstract_connection.h"
#include "../names/translate.h"

namespace ed
{
  class module;
  struct modules_translate : private translate
  {
    void AddModule( module *local, translate::id_type global )
    {
      translate::AddPair(*reinterpret_cast<translate::id_type *>(&local), global);
    }
    module *GetModule( id_type global ) const
    {
      return (module *)ToLocal(global);
    }
  };

  class gateway
  {
    com::abstract_connection &c;
    friend class module;
    int RegisterEvent( std::string name );
    bool PreNotify( const message &e );
    void PostNotify( const message &e);
    int instance;
    std::list<message> delayed_messages;
    modules_translate local_modules;
    int RegisterName( NAME_TYPE nt, std::string name );
    void CreateModule( std::string name, module *const );
  public:
    gateway( com::abstract_connection & );
    module &CreateModule( std::string name );
    bool QueryModule( int global_id, const message & );
  };
};

#include "module.h"

#endif