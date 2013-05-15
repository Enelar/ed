#ifndef _MODULE_AAA_H_
#define _MODULE_AAA_H_

#include "header.h"

class module_AAA : public ed::module
{
  void AllEventsListener( const event_context & );
public:
  module_AAA( ed::gateway _gw );
};

#endif
