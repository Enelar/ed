#include "connection.h"

bool handler;

connection::operator bool() const
{
  return !raw->disconnected;
}

connection::connection(bool _handler)
  : raw(make_shared<raw_connection>(_handler))
{
  receive_thread = async(&connection::ReceiveThread, this);
  receive_thread.wait_for(1ms);
}

connection::connection(const connection &that)
{
  memcpy(this, &that, sizeof(*this));
  new(&raw) decltype(raw)(that.raw);
}

connection::~connection()
{
  exit_flag = true;
}

void connection::ReceiveThread()
{
  while (!exit_flag)
  {
    this_thread::sleep_for(10ms);
    if (exit_flag)
      break;

    raw->mutex_handler.lock();
    vector<byte> gift;
    raw->mutex_handler.unlock();

    bool new_message;
    if (!new_message)
      continue;

    raw_message sure(&gift[0]);

    raw->mutex_received.lock();
    raw->received.push_back(sure);
    raw->mutex_received.unlock();
  }
}