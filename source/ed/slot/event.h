#ifndef _ED_SLOT_EVENT_H_
#define _ED_SLOT_EVENT_H_

#include "../notifications/event_source.h"
#include "../notifications/listener.h"
#include "../messages/listen.h"
#include <vector>
#include <set>

namespace ed
{
  struct slot_not_found
  {
  };
  namespace slot
  {
    struct event
    {
      std::vector<slot_data::listener> data;

      void AddListener( const listen_message &, bool force = true );
      void AddListener( const slot_data::listener &, bool force = true );
      void RemoveDisconnected( const int instance );

      std::set<int> Subscribed( int slot_data::listener::* type ) const;
    private:
      bool ListenerExist( const slot_data::listener & ) const;
    };
  };
};

template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator set_union (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, InputIterator2 last2,
                            OutputIterator result)
{
  while (true)
  {
    if (first1==last1) return std::copy(first2,last2,result);
    if (first2==last2) return std::copy(first1,last1,result);

    if (*first1<*first2) { *result = *first1; ++first1; }
    else if (*first2<*first1) { *result = *first2; ++first2; }
    else { *result = *first1; ++first1; ++first2; }
    ++result;
  }
}

#endif