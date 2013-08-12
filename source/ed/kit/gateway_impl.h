#ifndef _ED_GATEWAY_IMPL_H_
#define _ED_GATEWAY_IMPL_H_

namespace ed
{
  class module_impl;
  class gateway_impl
  {
    friend class gateway;
    gateway &gw;
    com::abstract_connection &c;
    friend class module;
    int RegisterEvent( std::string name );
    bool PreNotify( const message &e );
    void PostNotify( const message &e);
    int instance;
    std::list<message> delayed_messages;
    modules_translate local_modules;
    int RegisterName( NAME_TYPE nt, std::string name );
    void Listen( int source_instance, int dest_module, std::string module, std::string event );
    void Listen( int source_instance, int dest_module, int module, int event );

    typedef slot_data::instance instance_listener;

    instance_listener listeners;

    void CreateModule( std::string name, module_impl & );

    void IncomingNotification( message m );
    void DelegateNotification( const message &m );
  public:
    gateway_impl( gateway &, com::abstract_connection & );
    module &CreateModule( std::string name );
    bool QueryModule( int global_id, const message & );
    void Workflow();
  };
};

#endif