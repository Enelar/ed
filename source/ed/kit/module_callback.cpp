#include "module.h"

using namespace ed;
            

void module::EventReciever( const message &m )
{
  impl.EventReciever(m);
}

bool module::Query( const message &m )
{
  return impl.Query(m); 
}