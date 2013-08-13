#include "event.h"

using namespace ed::slot;
using namespace ed;

void event::AddListener( const listen_message &m, bool force )
{
  AddListener((slot_data::listener)m);
}

void event::AddListener( const slot_data::listener &m, bool force )
{
  if (ListenerExist(m))
    return;
  todo("Add listener to event");
}

bool event::ListenerExist( const slot_data::listener &m ) const
{
  todo("Is listener exsist");
}