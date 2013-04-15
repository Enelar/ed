#include "../ed/controllers/server_controller.h"
#include "../ed/communications/socket_ready.h"

using namespace ed;
using namespace ed::com;

#include <windows.h>

void main()
{
  socket_ready *port = NEW socket_ready(3030);
  server_controller<socket_ready> s(port);
  
  while (1)
  {
    Sleep(1);
    s.Workflow();
  }
}