#ifndef _ED_NOTIFICATIONS_INSTANCE_H_
#define _ED_NOTIFICATIONS_INSTANCE_H_

#include "event.h"

namespace ed
{
  namespace slot_data
  {
    struct module : public listeners_container <event>
    {
    };
    struct instance : public listeners_container<module>
    {
      void AddListener( int source_instance, int source_module, int source_event, listener destination )
      {
        todo("Add listener");
      }
    private:
    };
  };
};

#endif