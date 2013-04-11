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

      template<typename obj_type>
      void Each( obj_type & )
      {
        int i = 0, s = childs.size();
        for (;i < s; ++i)
          childs[i].Each(common_operator);
      }
    };

    struct listener
    {
      int instance, module;
    };
  };
};

#include "slot_data_utils.h"

#endif