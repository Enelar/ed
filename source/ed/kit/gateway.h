/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_KIT_GATEWAY_H_
#define _ED_KIT_GATEWAY_H_

namespace ed
{
  class module;
  template<class connection>
  class gateway
  {
  public:
    module &CreateModule( std::string name );
  };
};

#endif