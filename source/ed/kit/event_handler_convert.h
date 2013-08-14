#ifndef _ED_KIT_EVENT_HANDLER_CONVERT_H_
#define _ED_KIT_EVENT_HANDLER_CONVERT_H_

#include "event_context.h"

namespace ed
{
  template<typename RET>
  class event_handler_adapter
  {
  public:
    virtual RET FarCall( const event_context<> &_obj ) = 0;
  };

  template<typename MODULE, typename T, typename RET>
  class event_handler_convert : public event_handler_adapter<RET>
  {
  public:
    typedef event_context<T> prefferedT;
    typedef RET (MODULE::*childT)( const prefferedT & );
    typedef RET (*parentT)( const event_context<> & );

    static childT Specific( parentT f )
    {
      return reinterpret_cast<childT>(f);
    }
    static parentT Generic( childT f )
    {
      return reinterpret_cast<parentT>(f);
    }
  private:
    MODULE &m;
    childT origin;
  public:
    event_handler_convert( MODULE &_m, childT _origin ) : m(_m), origin(_origin)
    {}

    virtual RET FarCall( const event_context<> &_obj )
    {
      prefferedT obj = convert<prefferedT>(_obj);
      childT f = origin;

      return (m.*f)(obj);
    }
  };
};

#endif