#ifndef _ED_KIT_EVENT_HANDLER_CONVERT_H_
#define _ED_KIT_EVENT_HANDLER_CONVERT_H_

#include "event_context.h"

namespace ed
{
  template<typename T>
  class event_handler_convert;

  template<typename T>
  class event_handler_convert
  {
  public:
    typedef event_context<T> prefferedT;
    typedef void (*childT)( const prefferedT & );
    typedef void (*parentT)( const event_context<> & );

    static childT Convert( parentT f )
    {
      return reinterpret_cast<childT>(f);
    }
    static parentT Convert( childT f )
    {
      return reinterpret_cast<parentT>(f);
    }
  public:
    virtual void FarCall( parentT _f, event_context<> &_obj )
    {
      prefferedT obj = _obj;
      childT f = _f;

      f(obj);
    }
  };
};

#endif