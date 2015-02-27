#include "ctrler.h"

ctrler::ctrler(int port)
  : core(*this)
{
  accept_future = async(&ctrler::AcceptThread, this, port);
  accept_future.wait_for(1ms);
}

ctrler::~ctrler()
{
  exit_flag = true;
}

void ctrler::AcceptThread(int port)
{
  while (!exit_flag)
  {
    this_thread::sleep_for(100ms);
    if (exit_flag)
      break;

    auto new_connection = connection(true);
    if (!new_connection)
      continue;

    mutex_connections.lock();
    connections.insert({free_connection_id++, new_connection});
    mutex_connections.unlock();
  }
}