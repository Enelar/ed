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

void ctrler::MessageThread()
{
  while (!exit_flag)
  {
    this_thread::sleep_for(100ms);
    if (exit_flag)
      break;

    mutex_connections.lock();
    for (auto &customer : connections)
    {
      auto &messages = customer.second.raw->received;
      auto id = customer.first;
      while (messages.size())
      {
        auto gift = messages.front();
        messages.pop_front();
        OnMessage(id, gift);
      }
    }
    mutex_connections.unlock();
  }
}

void ctrler::OnMessage(int id, raw_message &message)
{
  message.from.instance = id;

  if (message.to.instance != ed::reserved::instance::CONTROLLER)
  { // Just proxy message
    switch (message.to.instance)
    {
    case ed::reserved::instance::BROADCAST:
      for (auto &customer : connections)
        Send(message, customer.first);
      break;
    case ed::reserved::instance::MASTER:
      throw "TODO;";
    default:
      Send(message, message.to.instance);
    }
    return;
  }

  // Additional action required
  switch (message.event)
  {
  case ed::reserved::event::MODULE_NAME_LOOKUP:
  case ed::reserved::event::EVENT_NAME_LOOKUP:
    core.Translate(message);
    break;
  case ed::reserved::event::LISTEN:
    core.Listen(message);
    break;
  case ed::reserved::event::INSTANCE_UP:
  case ed::reserved::event::MODULE_UP:
    core.Up(message);
    break;
  }
}