#define _ED_NOTIFICATIONS_SLOT_IMPL_
#ifndef _ED_NOTIFICATIONS_SLOT_H_
#include "slot.h"
#endif

#define _TEMPLATE_ slot<connection>

template<typename connection>
_TEMPLATE_::slot( connection *_socket )
  : c(NEW container(_socket))
{
  throw_assert(_socket);
}

template<typename connection>
_TEMPLATE_::slot( const slot &a )
  : c(NULL)
{
  (*this) = a;
}

template<typename connection>
_TEMPLATE_ &_TEMPLATE_::operator=( const slot &a )
{
  if (this == &a)
    return *this;
  throw_assert(a.c);
  if (c != NULL)
    c->RemoveShare();
  c = a.c;
  c->AddShare();
  throw_assert(c->socket);
  return *this;
}

template<typename connection>
connection &_TEMPLATE_::Socket() const
{
  return *c->socket;
}

template<typename connection>
_TEMPLATE_::~slot()
{
  c->RemoveShare();
}


#undef _TEMPLATE_