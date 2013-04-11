/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_SLOT_DATA_UTILS_H_
#define _ED_NOTIFICATIONS_SLOT_DATA_UTILS_H_

#include "slot_data.h"
#include "listener_container.h"
#include "event.h"
#include "../exceptions/exception.h"
#include <list>

namespace ed
{
  namespace slot_data
  {
    typedef listeners_container <event> module;
    typedef listeners_container <module> instance;

    class RemoveInstance
    {
      int id;
    public:
      RemoveInstance( int _id ) : id(_id)
      {}
      void Commit( event &e )
      {
        std::list<int> to_remove;
        int i = 0, s = e.childs.size();
        for (; i < s; ++i)
          if (e.childs[i].instance == id)
            to_remove.push_back(i);
        todo("Perform remove wrong listeners");
      }
    };
  };
};


#endif