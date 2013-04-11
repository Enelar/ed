/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_SLOT_H_
#define _ED_NOTIFICATIONS_SLOT_H_

#include <vector>

namespace ed
{
  namespace slot_data
  {
    struct listener
    {
      int instance, module;
    };
    
    struct event
    {
      std::vector<listener> listeners;
    };
    
    struct module
    {
      std::vector<event> events;
    };
    
    struct instance
    {
      std::vector<module> modules;
    };
  };
  template<class connection>
  class slot : public slot_data::instance
  {
    connection socket;
  };
};

#ifndef _ED_NOTIFICATIONS_SLOT_IMPL_
namespace ed
{
  #include "slot.cpp"
};
#endif

#endif
