#include "header.h"

using namespace ed;

enum DUMMY_EVENTS
{
  TEST_EVENT
};

void f()
{
  com::socket_connection port("localhost", 3030);
  gateway gw(port);
  module m("test", gw);
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