#ifndef _ED_NOTIFICATIONS_SLOT_H_
#define _ED_NOTIFICATIONS_SLOT_H_

#include "slot_data.h"
#include "instance.h"
#include <vector>

#include "../3party/ax/types.h"

namespace ed
{
  template<class connection>
  class slot : public slot_data::instance
  {
    struct container : ax::shared_self_controlled
    {
      connection *socket;

      container( connection *_socket )
        : socket(_socket)
      {
        AddShare();
      }
      ~container()
      {
        delete socket;
      }
    };
    container *c;
  public:

    slot( connection * );
    slot( const slot & );
    slot &operator=( const slot & );
    connection &Socket() const;
    ~slot();
  };
};

#ifndef _ED_NOTIFICATIONS_SLOT_IMPL_
namespace ed
{
  #include "slot.cpp"
};
#else
using namespace ed;
#endif

#endif
