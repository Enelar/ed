#ifndef _MODULE_BBB_H_
#define _MODULE_BBB_H_

#include "header.h"

class module_BBB : public ed::module
{
  bool CheckAAAEventTEST( const event_context & );
public:
  module_BBB( ed::gateway &_gw );
  void SendTestEvents();
};

#endif
