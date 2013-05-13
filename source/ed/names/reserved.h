#ifndef _ED_NAMES_RESERVERD_H_
#define _ED_NAMES_RESERVERD_H_

namespace ed
{
  namespace reserved
  {
    namespace instance
    {
      enum INSTANCE
      {
        BROADCAST = 0,
        MASTER = 1,
        CONTROLLER = 2,
        FIRST_ALLOWED = 16
      };
    };

    namespace module
    {
      enum MODULE
      {
        BROADCAST = 0,
        HEART_BEAT = 1,
        FIRST_ALLOWED = 16
      };
    }

    namespace event
    {
      enum EVENT
      {
        BROADCAST = 0,
        INSTANCE_UP,
        MODULE_UP,
        EVENT_REGISTER,
        LISTEN = 4,
        RESERVED_5 = 5,
        MODULE_NAME_LOOKUP = 6,
        EVENT_NAME_LOOKUP = 7,
        MODULE_GLOBAL_ID_REQUEST = 8,
        EVENT_GLOBAL_ID_REQUEST = 9,
        FIRST_ALLOWED = 16
      };
    };
  };
};

#endif
