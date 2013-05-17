#ifndef _ED_NOTIFICATIONS_INSTANCE_H_
#define _ED_NOTIFICATIONS_INSTANCE_H_

#include "slot.h"
#include "event.h"

namespace ed
{
  namespace slot_data
  {
    struct module : public listeners_container <event>
    {
      friend struct instance;
    private:
      void CreateEvent( unsigned int id )
      {
        CreateElement(id);
      }
    };
    struct instance : public listeners_container<module>
    {
      void AddListener( event_source source, listener destination )
      {
        slot_data::event *e = GetEvent(source);
        if (!e)
        {
          CreateEvent(source.module, source.event);
          throw_assert(e = GetEvent(source));
        }
        e->childs.push_back(listener());
      }
    private:
      void CreateEvent( unsigned int module, unsigned event )
      {
        CreateModule(module);
        childs[module].CreateElement(event);
      }
      void CreateModule( unsigned int id )
      {
        CreateElement(id);
      }
    };
  };
};

#endif