#ifndef _ED_NOTIFICATIONS_LISTENER_H_
#define _ED_NOTIFICATIONS_LISTENER_H_

namespace ed
{
  namespace slot_data
  {
    struct __declspec(dllexport) listener
    {
      int instance, module;
    };
  };
};

#endif