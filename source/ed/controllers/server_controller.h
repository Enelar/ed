#ifndef _ED_SERVER_CONTROLLER_H_
#define _ED_SERVER_CONTROLLER_H_

#include "../communications/connection_ready.h"
#include "../communications/abstract_connection.h"
#include "../names/name_server.h"
#include "../notifications/listener.h"

namespace ed
{
  struct server_controller_impl;
  struct _ED_DLL_EXPORT_ server_controller
  {
    friend server_controller_impl;
    server_controller_impl &impl;
    typedef com::connection_ready ready_type;
    typedef com::abstract_connection connection;
    typedef name_server::id_type id_type;
    typedef name_server::word_type word_type;
    typedef slot_data::listener listener;
  public:
    server_controller( ready_type & );
    ~server_controller();
    id_type RegisterName( NAME_TYPE nt, word_type name );
    void AddListener( event_source source, listener destination );
    void MakeNotification( message &, const event_source &search_source );
    void Workflow();
  };
};

#include "../names/reserved.h"
#include "../messages/listen.h"
#include <iostream>

#endif
