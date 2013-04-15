/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_SLOT_DATA_H_
#define _ED_NOTIFICATIONS_SLOT_DATA_H_

#include <vector>
#include "../exceptions/exception.h"

namespace ed
{
  namespace slot_data
  {
    
    template<typename child_type>
    struct common_container
    {
      std::vector<child_type> childs;

      template<typename obj_type>
      void Each( obj_type &common_operator )
      {
        int i = 0, s = childs.size();
        for (;i < s; ++i)
          childs[i].Each(common_operator);
      }
      
      template<typename obj_type>
      void Direct( obj_type &a )
      {
        unsigned int target = a.Target();
        throw_assert(target >= 0);
        throw_assert(target < childs.size());
        a.Direct(childs[target]);
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