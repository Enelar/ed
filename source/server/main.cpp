#include "../ed/controllers/server_controller.h"
#include "../ed/controllers/client_controller.h"
#include "../ed/communications/socket_ready.h"

using namespace ed;
using namespace ed::com;

#include <windows.h>

void main()
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