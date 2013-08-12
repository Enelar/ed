#include "server_controller_impl.h"

using namespace ed;

#define _TEMPLATE_HEAD_ 
#define _TEMPLATE_ server_controller

_TEMPLATE_HEAD_
_TEMPLATE_::server_controller( ready_type *_ready )
  : impl(*NEW server_controller_impl(_ready))
{
}

_TEMPLATE_HEAD_
_TEMPLATE_::~server_controller( )
{
  delete &impl;
}

_TEMPLATE_HEAD_
_TEMPLATE_::id_type _TEMPLATE_::RegisterName( NAME_TYPE nt, word_type name )
{
  return impl.RegisterName(nt, name);
}

_TEMPLATE_HEAD_
void _TEMPLATE_::AddListener( event_source source, listener destination )
{
  impl.AddListener(source, destination);
}

_TEMPLATE_HEAD_
void _TEMPLATE_::MakeNotification( message &a, const event_source &search_source )
{
  impl.MakeNotification(a, search_source);
}

_TEMPLATE_HEAD_
void _TEMPLATE_::Workflow()
{
  impl.Workflow();
}