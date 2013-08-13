#ifndef _ED_NOTIFICATIONS_LISTENER_H_
#define _ED_NOTIFICATIONS_LISTENER_H_

namespace ed
{
  namespace slot_data
  {
    struct listener
    {
      int instance, module;

      bool operator==( const listener &a ) const
      {
        return instance == a.instance && module == a.module;
      }
    };
  };
};

#endif