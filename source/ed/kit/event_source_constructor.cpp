#include "event_source_constructor.h"

using namespace ed;

event_source_constructor::event_source_constructor()
 : 
  instance(es.instance, INSTANCES),
  module(es.module, MODULES),
  event(es.event, EVENTS)
{
}

event_source_constructor::operator ed::event_source() const
{
  return es;
}

// 

#include "../exceptions/exception.h"

void event_source_constructor::event_source_partial_translator::ByLocal( int id )
{
  todo("by local");
}

void event_source_constructor::event_source_partial_translator::ByGlobal( int id )
{
  dep = id;
}

void event_source_constructor::event_source_partial_translator::ByName( const std::string &name )
{
  todo("by name");
}