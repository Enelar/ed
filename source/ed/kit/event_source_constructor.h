#ifndef _ED_KIT_EVENT_SOURCE_CONSTRUCTOR_H_
#define _ED_KIT_EVENT_SOURCE_CONSTRUCTOR_H_

#include "../notifications/event_source.h"
#include "../names/name_type.h"

#include <string>

namespace ed
{
  class event_source_constructor
  {
    event_source es;

    class event_source_partial_translator
    {
      int &dep;
      NAME_TYPE nt;
    public:
      event_source_partial_translator( int &dependent, NAME_TYPE _nt )
        : dep(dependent), nt(_nt)
      {
      }
      void ByLocal( int id );
      void ByGlobal( int id );
      void ByName( const std::string &name );
    };
  public:
    event_source_partial_translator
      instance, module, event;

    event_source_constructor();

    operator event_source() const;
  };
};

#endif