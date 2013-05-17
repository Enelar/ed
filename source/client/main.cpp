#include "header.h"

using namespace ed;

#include "module_AAA.h"
#include "module_BBB.h"

void f()
{
  com::socket_connection port("localhost", 3030);
  gateway gw(port);
  module_AAA a(gw);
  module_BBB b(gw);
  gw.Workflow();
  a.SendTestEvents();
  gw.Workflow();
  b.SendTestEvents();
  gw.Workflow();
  gw.Workflow();
  gw.Workflow();
}

#include <iostream>

void main()
{
  ed::Sleep(500);
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