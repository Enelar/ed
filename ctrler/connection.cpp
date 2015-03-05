#include "connection.h"
#include <iostream>

bool handler;

connection::operator bool() const
{
  return !raw->disconnected;
}

connection::connection(raw_connection::handlerT *_handler)
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
  const auto first_part_size = message_header::raw_byte_size + 4;
  vector<byte> header;
  header.resize(first_part_size);

  auto PayloadSize = [&header]()
  {
    if (header.size() < 4)
      throw "something wrong with header buffer";
    auto offset = header.size() - 4;
    return *(int *)&header[0];
  };

  bool read_header_state = true;

  while (!exit_flag)
  {
    this_thread::sleep_for(10ms);
    if (exit_flag)
      break;

    raw->mutex_handler.lock();
    auto ready = raw->handler->available();
    if (read_header_state)
    {
      if (ready < first_part_size)
      {
        raw->mutex_handler.unlock();
        continue; // we ignore not complete messages
      }

      cout << "Get message header!!!" << endl;

      read(*raw->handler, boost::asio::buffer(header, first_part_size));
      read_header_state = false;
      ready = raw->handler->available();
    }

    if (ready < PayloadSize())
    {
      raw->mutex_handler.unlock();
      continue;
    }

    raw_message sure;
    sure.Fill(message_header(&header[0]));
    sure.payload.resize(PayloadSize());
    read(*raw->handler, boost::asio::buffer(sure.payload));

    raw->mutex_handler.unlock();
    read_header_state = true;

    cout << "Get full message!!! " << sure.event << endl;

    {
      raw->mutex_received.lock();
      raw->received.push_back(sure);
      raw->mutex_received.unlock();
    }
  }
}

void connection::Send(raw_message &)
{
  raw->mutex_send.lock();
  raw->mutex_send.unlock();
}