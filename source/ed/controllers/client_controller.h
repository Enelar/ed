#ifndef _ED_CONTROLLERS_CLIENT_CONTROLLER_H_
#define _ED_CONTROLLERS_CLIENT_CONTROLLER_H_

namespace ed
{
  template<class connection>
  struct client_controller
  {
  private:
    connection *c;
  public:
    client_controller( connection * );

    operator connection &() const;

    ~client_controller();
  };
};

#ifndef _ED_CONTROLLERS_CLIENT_CONTROLLER_IMPL_
namespace ed
{
  #include "client_controller.cpp"
};
#else
using namespace ed;
#endif

#endif