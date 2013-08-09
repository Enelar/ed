#ifndef _ED_KIT_EVENT_HANDLER_CONVERT_H_
#define _ED_KIT_EVENT_HANDLER_CONVERT_H_

namespace ed
{
  template<typename T>
  class event_handler_convert;

  template<typename T>
  class event_handler_convert
  {
    typedef void event_context<T> preffered_type;
    typedef void (*childT)( const preffered & );
    typedef void (*parentT)( const event_context<> & );

    childT Convert( parentT f )
    {
      return reinterpret_cast<childT>(f);
    }
  public:
    virtual void FarCall( parent_T _f, event_context<> &_obj )
    {
      preffered_type obj = _obj;
      childT f = _f;

      f(obj);
    }
  };
};

#endif