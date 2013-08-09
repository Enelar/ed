#ifndef _MODULE_AAA_H_
#define _MODULE_AAA_H_

#include "header.h"

struct my_type : public ed::event_data
{
};

class module_AAA : public ed::module
{
  void AllEventsListener( const ed::event_context<> & );
  void MyTypeExample( const ed::event_context<my_type> & );
public:
  module_AAA( ed::gateway &_gw );
  void SendTestEvents();
};

#endif
