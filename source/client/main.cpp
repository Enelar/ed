#include "../ed/exceptions/exception.h"
#include "../ed/kit/gateway.h"
#include "../ed/communications/socket_connection.h"

using namespace ed;

void f()
{
  com::socket_connection port("localhost", 3030);
  gateway gw(port);
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
  }
}