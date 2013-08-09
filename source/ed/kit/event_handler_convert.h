#ifndef _ED_KIT_EVENT_HANDLER_CONVERT_H_
#define _ED_KIT_EVENT_HANDLER_CONVERT_H_

#include "event_context.h"

namespace ed
{
  template<typename T, typename RET>
  class event_handler_convert;

  class unused_internal_type
  {
  };

  template<typename RET>
  class event_handler_convert<unused_internal_type, RET>
  {
  public:
    virtual RET FarCall( event_context<> &_obj ) = 0;
  };

  template<typename T, typename RET>
  class event_handler_convert : public event_handler_convert<unused_internal_type, RET>
  {
  public:
    typedef event_context<T> prefferedT;
    typedef RET (*childT)( const prefferedT & );
    typedef RET (*parentT)( const event_context<> & );

    static childT Convert( parentT f )
    {
      return reinterpret_cast<childT>(f);
    }
    static parentT Convert( childT f )
    {
      return reinterpret_cast<parentT>(f);
    }
  private:
    childT origin;
  public:
    event_handler_convert( childT _origin ) : origin(_origin)
    {}

    virtual RET FarCall( event_context<> &_obj )
    {
      prefferedT obj = _obj;
      childT f = origin;

      f(obj);
    }
  };
};

#endif