#ifndef _ED_SERVER_CONTROLLER_H_
#define _ED_SERVER_CONTROLLER_H_

#include "../names/name_server.h"
#include "../notifications/slot.h"
#include "../notifications/event_notification.h"
#include <vector>
#include "../communications/connection_ready.h"
#include "../communications/abstract_connection.h"

namespace ed
{
  struct __declspec(dllexport) server_controller
  {
    typedef name_server::id_type id_type;
    typedef name_server::word_type word_type;
    typedef slot_data::listener listener;
  private:
    typedef com::connection_ready ready_type;
    typedef com::abstract_connection connection;
    typedef slot<connection> client_type;

    name_server &names;
    std::vector<client_type> &clients;
    ready_type *ready;
  public:
    server_controller( ready_type * );
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
