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
      typedef std::vector<child_type> container_type;
      container_type childs;

      template<typename obj_type>
      void Each( obj_type &common_operator )
      {
        int i = 0, s = childs.size();
        for (;i < s; ++i)
          childs[i].Each(common_operator);
      }

      bool Exists( int target )
      {
        return target >= 0 && (unsigned)target < childs.size();
      }

      template<typename obj_type>
      void Direct( obj_type &a )
      {
        unsigned int target = a.Target();
        throw_assert(Exists(target));
        a.Direct(childs[target]);
      }

      template<typename obj_type>
      void IfExists( obj_type &a )
      {
        unsigned int target = a.Target();
        if (Exists(target))
          a.IfExists(childs[target]);
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