#include "ctrler.h"
#include <iostream>
#include <ed/structs/messages/handshake.h>

using namespace boost::asio::ip;
ctrler::ctrler(boost::asio::io_service &_io, int port)
  : core(*this), io(_io), accept_socket(io, tcp::endpoint(address::from_string("0.0.0.0"), port))
{
  accept_future = async(&ctrler::AcceptThread, this, port);
  accept_future.wait_for(1ms);

  message_future = async(&ctrler::MessageThread, this);
  message_future.wait_for(1ms);
}

ctrler::~ctrler()
{
  exit_flag = true;
}

void ctrler::AcceptThread(int port)
{
  semaphore_strict ready;
  unique_ptr<tcp::socket> socket;

  auto AcceptCallback = [&ready, this, &socket](const boost::system::error_code& error)
  {
    if (error)
    {
      ready.unlock();
      return;
    }

    auto raii = mutex_connections.Lock();
    connection new_connection(socket.release());
    cout << "NEW CONNECTION" << free_connection_id << endl;
    connections.insert({ free_connection_id++, new_connection });

    ready.unlock();
  };

  while (!exit_flag)
  {
    this_thread::sleep_for(100ms);
    if (exit_flag)
      break;
    if (!ready.try_lock())
      continue;

    if (socket)
      throw "weird stuff here";

    socket = make_unique<tcp::socket>(io);
    accept_socket.async_accept(*socket, AcceptCallback);
  }
  accept_socket.close();
}

void ctrler::Send(raw_message gift)
{
  Send(gift, gift.to.instance);
}

void ctrler::Send(raw_message gift, int id)
{
  auto customer = connections.find(id);
  if (customer == connections.end())
    throw "Support disconnected and wrong adressed messages";
  customer->second.Send(gift);
}

void ctrler::MessageThread()
{
  while (!exit_flag)
  {
    this_thread::sleep_for(100ms);
    if (exit_flag)
      break;

    auto connection_guard = mutex_connections.Lock();
    vector<int> to_remove;
    for (auto &customer : connections)
    {
      auto id = customer.first;
      auto &raw = customer.second.raw;
      auto &messages = raw->received;

      try
      {
        // i dont care of performance
        auto raii = raw->mutex_received.Lock();
        while (messages.size())
        {
          auto gift = messages.front();
          messages.pop_front();
          if (customer.second.raw->handshake_required)
          {
            OnHandshake(id, gift);
            customer.second.raw->handshake_required = false;
            cout << "HEY! " << id << " JUST HANDSHAKED!!" << endl;
          }
          else
            OnMessage(id, gift);
        }
      }
      catch (const char *debug_message)
      {
        cout << debug_message << endl;
        to_remove.push_back(id);
      }
      catch (...)
      {
        to_remove.push_back(id);
#ifdef _DEBUG
        throw; // rethrow, we in debug.
#endif
      }
    }

    for (auto id : to_remove)
    {
      connections.erase(id);
      cout << "FORCE DISCONNECT " << id << endl;
    }
  }
}

void ctrler::OnHandshake(int id, messages::handshake gift)
{
  Send(messages::handshake(), id);

  if (gift.payload.version != ed::reserved::protocol_version)
    throw "sad by we should kick you...";
}

void ctrler::OnMessage(int id, raw_message message)
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