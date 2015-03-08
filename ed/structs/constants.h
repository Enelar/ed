#pragma once

#include "../contants_debug_strings.h"

namespace ed
{
  namespace reserved
  {
    static const int protocol_version = 1;

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
        NAMES = 2,
        LISTEN = 3,
        FIRST_ALLOWED = 16
      };
    }
    namespace event
    {
      enum EVENT
      {
        BROADCAST = 0,
        INSTANCE_UP = 1,
        MODULE_UP = 2,
        LISTEN = 3,
        DIRECT_SEND = 4,
        EXCLUSIVE_SEND = 5,

        MODULE_NAME_LOOKUP = 6,
        EVENT_NAME_LOOKUP = 7,
        MODULE_GLOBAL_ID_REQUEST = 8,
        EVENT_GLOBAL_ID_REQUEST = 9,

        INSTANCE_DOWN = 11,
        MODULE_DOWN = 12,

        FIRST_ALLOWED = 16
      };
    };
  };
};