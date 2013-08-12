/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Develop Project agreement
 * No part of this file could be used or viewed without Develop Project agreement
 */

#ifndef _AX_TYPES_H_
#define _AX_TYPES_H_

namespace ax
{
  class __declspec(dllexport) object
  {
  public:
    virtual ~object()
    {}
  };
  class __declspec(dllexport) copyable : public object
  {
  public:
    virtual copyable *Copy( void ) const = 0;
  };
  class __declspec(dllexport) shared : public object
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
  class __declspec(dllexport) shared_self_controlled : public shared
  {
  public:
    virtual void RemoveShare( );
  };
};
#endif