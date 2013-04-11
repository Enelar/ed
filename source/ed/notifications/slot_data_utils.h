/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_SLOT_DATA_UTILS_H_
#define _ED_NOTIFICATIONS_SLOT_DATA_UTILS_H_

#include "slot_data.h"
#include "../exceptions/exception.h"
#include <list>

namespace ed
{
  namespace slot_data
  {
    class RemoveInstance;
    template<typename child_type>
    struct listeners_container : public common_container<child_type>
    {
      void RemoveDisconnectedInstance( int id )
      {
        Each(RemoveInstance(id));
      }
    };

    struct event : public listeners_container<listener>
    {
      template<typename obj_type>
      void Each( obj_type &a )
      {
        a.Commit(*this);
      }
    };

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
        std::list<int> to_delete;
        int i = 0, s = e.childs.size();
        for (; i < s; ++i)
          if (e.childs[i].instance == id)
            to_delete.push_back(i);
        todo("Perform delete wrong listeners");
      }
    };
  };
};


#endif