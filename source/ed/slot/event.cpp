#include "event.h"

using namespace ed::slot;
using namespace ed;

void event::AddListener( const listen_message &m )
{
  if (ListenerExist(m))
    return;
  todo("Add listener to event");
}