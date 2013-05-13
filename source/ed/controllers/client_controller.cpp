#define _ED_CONTROLLERS_CLIENT_CONTROLLER_IMPL_
#ifndef _ED_CONTROLLERS_CLIENT_CONTROLLER_H_
#include "client_controller.h"
#endif

#define _TEMPLATE_ client_controller<connection>

#include "../exceptions/exception.h"

template<class connection>
_TEMPLATE_::client_controller( connection *_c ) : c(_c)
{
  throw_assert(_c);
}

template<class connection>
_TEMPLATE_::~client_controller()
{
  delete c;
}

template<class connection>
_TEMPLATE_::operator connection &() const
{
  return *c;
}

#undef _TEMPLATE_