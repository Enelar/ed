#ifndef _ED_KIT_EVENT_SOURCE_CONSTRUCTOR_H_
#define _ED_KIT_EVENT_SOURCE_CONSTRUCTOR_H_

#include "../notifications/event_source.h"
#include "../names/name_type.h"

#include <string>

namespace ed
{
  class module_impl;
  class event_source_constructor
  {
    event_source es;
    module_impl &gw;

    class event_source_partial_translator
    {
      int &dep;
      NAME_TYPE nt;
      module_impl &gw;
    public:
      event_source_partial_translator( module_impl &_gw, int &dependent, NAME_TYPE _nt )
        : dep(dependent), nt(_nt), gw(_gw)
      {
      }
      void ByLocal( int id );
      void ByGlobal( int id );
      void ByName( const std::string &name );
    };
  public:
    event_source_partial_translator
      instance, module, event;

    event_source_constructor( module_impl &gw );

    operator event_source() const;
  };
};

#endif