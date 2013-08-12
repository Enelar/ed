#include "../ed/controllers/server_controller.h"
#include "../ed/controllers/client_controller.h"
#include "../ed/communications/socket_ready.h"
#include "../ed/exceptions/exception.h"

using namespace ed;
using namespace ed::com;

#include <windows.h>

void f()
{
  socket_ready *port = NEW socket_ready(3030);
  server_controller<socket_ready> s(port);
  socket_ready::pair_type *socket = NEW socket_ready::pair_type("localhost", 3030);
  client_controller<socket_ready::pair_type> c(socket);

  while (1)
  {
    Sleep(1);
    s.Workflow();
  }
}

#include <iostream>

void main()
{
  Sleep(1);
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