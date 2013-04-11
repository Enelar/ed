/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_SLOT_DATA_H_
#define _ED_NOTIFICATIONS_SLOT_DATA_H_

#include <vector>

namespace ed
{
  namespace slot_data
  {
    template<typename child_type>
    struct common_container
    {
      std::vector<child_type> childs;
    };

    struct listener
    {
      int instance, module;
    };
    
    typedef common_container<listener> event;
    typedef common_container<event> module;
    typedef common_container<module> instance;
  };
};

#endif