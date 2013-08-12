/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Develop Project agreement
 * No part of this file could be used or viewed without Develop Project agreement
 */

#ifndef _AX_TYPES_H_
#define _AX_TYPES_H_

#include "../../def.h"

namespace ax
{
  class _ED_DLL_EXPORT_ object
  {
  public:
    virtual ~object()
    {}
  };
  class _ED_DLL_EXPORT_ copyable : public object
  {
  public:
    virtual copyable *Copy( void ) const = 0;
  };
  class _ED_DLL_EXPORT_ shared : public object
  {
  protected:
    typedef unsigned int dword;
    dword users;
  public:
    shared();
    virtual void AddShare( );
    virtual void RemoveShare( );
    ~shared();
  };
  class _ED_DLL_EXPORT_ shared_self_controlled : public shared
  {
  public:
    virtual void RemoveShare( );
  };
};
#endif