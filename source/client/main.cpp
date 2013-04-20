#include "../ed/exceptions/exception.h"
#include "../ed/exceptions/disconnected.h"
#include "../ed/kit/gateway.h"
#include "../ed/kit/module.h"
#include "../ed/communications/socket_connection.h"

using namespace ed;

void f()
{
  com::socket_connection port("localhost", 3030);
  gateway gw(port);
  module &m = gw.CreateModule("test");
}

#include <iostream>

void main()
{
  //BREAK_ON_MEMORY_LEAK(274);
  try
  {
    f();
  } catch (ed::exception *e)
  {
    std::cout << *e << std::endl;
    delete e;
  } catch (ed::disconnected *e)
  {
    std::cout << "Disconnected";
    delete e;
  }
}