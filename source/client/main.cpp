#include "../ed/exceptions/exception.h"
#include "../ed/exceptions/disconnected.h"
#include "../ed/kit/gateway.h"
#include "../ed/kit/module.h"
#include "../ed/communications/socket_connection.h"
#include "../ed/3party/win/utils.h"

using namespace ed;

enum DUMMY_EVENTS
{
  TEST_EVENT
};

void f()
{
  com::socket_connection port("localhost", 3030);
  gateway gw(port);
  module &m = gw.CreateModule("test");
  m.RegisterEvent(TOSTRING(TEST_EVENT), TEST_EVENT);
  {
    event_result a = m.SendEvent(TEST_EVENT);
  }
  delete &m;
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