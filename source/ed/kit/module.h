/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_KIT_MODULE_H_
#define _ED_KIT_MODULE_H_

#include "gateway.h"

namespace ed
{
  class module
  {
    friend class gateway;
    module( gateway & );
    gateway &gw;
  protected:
    void RegisterEvent( std::string name, int local_id );
  };
};

#endif