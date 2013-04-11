/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_NOTIFICATIONS_SLOT_DATA_UTILS_H_
#define _ED_NOTIFICATIONS_SLOT_DATA_UTILS_H_

#include "event.h"
#include "event_notification.h"
#include "../exceptions/exception.h"
#include <list>

namespace ed
{
  namespace slot_data
  {
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

    class AddListener
    {
      static const int target_count = 3;
      int targets[target_count];
      int level;
      listener dest;
    public:
      AddListener( event_source es, listener destination ) :
        level(0), dest(destination)
      {
        targets[0] = es.instance;
        targets[1] = es.module;
        targets[2] = es.event;
      }

      int Target() const
      {
        return targets[level];
      }

      template<typename obj>
      void Direct( obj &a )
      {
        ++level;
        throw_assert(level < target_count);
        a.Direct(*this);
      }

      virtual void Direct( event &a )
      {
        throw_assert(level == target_count);
        a.childs.push_back(dest);
      }
    };

    //! @NOTE Not really good..
    struct module;
    class SearchEvent
    {
      static const int target_count = 3;
      int targets[target_count];
      int level;
    public:
      SearchEvent( event_source es ) :
        level(0)
      {
        targets[0] = es.instance;
        targets[1] = es.module;
        targets[2] = es.event;
      }

      int Target() const
      {
        return targets[level];
      }

      template<typename obj>
      void Direct( obj &a )
      {
        ++level;
        throw_assert(level < target_count);
        a.Direct(*this);
      }

      event *e;

      void Direct( module &m );
    };
  };
};


#endif