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
};

#include "gateway_impl.h"

namespace ed
{
  struct register_answer;
  class _ED_DLL_EXPORT_ gateway
  {
    gateway_impl &impl;

    friend class gateway_impl;
    friend class module_impl;
    friend class module;

    int RegisterEvent( std::string name );
    bool PreNotify( const message &e );
    void PostNotify( const message &e);
    int RegisterName( NAME_TYPE nt, std::string name );
    void Listen( int source_instance, int dest_module, std::string module, std::string event );
    void Listen( int source_instance, int dest_module, int module, int event );

    void CreateModule( std::string name, module_impl & );

    void IncomingNotification( message m );
    void DelegateNotification( const message &m );
  public:
    gateway( com::abstract_connection & );
    module &CreateModule( std::string name );
    bool QueryModule( int global_id, const message & );
    void Workflow();
    ~gateway();
  };
};

#include "module.h"

#endif