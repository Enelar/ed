/*
#include "module.h"
#include "event_handler_convert.h"

static childT event_handler_convert::Convert( parentT f )
{
  return reinterpret_cast<childT>(f);
}
static parentT event_handler_convert::Convert( childT f )
{
  return reinterpret_cast<parentT>(f);
}             */