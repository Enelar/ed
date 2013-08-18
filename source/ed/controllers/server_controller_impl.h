#ifndef _ED_CONTROLLERS_SERVER_CONTROLLER_H_
#define _ED_CONTROLLERS_SERVER_CONTROLLER_H_

#include "server_controller.h"
#include "../slot/route.h"
#include "../notifications/event_notification.h"
#include <vector>


namespace ed
{
  struct server_controller_impl
  {
    typedef name_server::id_type id_type;
    typedef name_server::word_type word_type;
    typedef slot_data::listener listener;
  private:
    typedef com::connection_ready ready_type;
    typedef com::abstract_connection connection;
    //typedef slot client_type;

    name_server names;
    slot::route clients;
    ready_type &ready;
  public:
    server_controller_impl( ready_type & );
    ~server_controller_impl();
    id_type RegisterName( NAME_TYPE nt, word_type name );
    void AddListener( event_source source, listener destination );
    void MakeNotification( int i, const message & );
    void Workflow();
    void SysWorkflow( int i, connection &socket );

    void RegisterWorkflow( int i, connection &socket, const register_message & );
    void ListenWorkflow( int i, connection &socket, const listen_message & );
    void NotifyWorkflow( int i, connection &socket, const message & );
  };
};

#endif