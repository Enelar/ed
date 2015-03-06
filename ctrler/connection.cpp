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
}

connection::connection(const connection &that)
  : raw(that.raw)
{
}

connection::~connection()
{
}

raw_connection::raw_connection(handlerT *a)
  : handler(a)
{
  receive_thread = async(&raw_connection::ReceiveThread, this);
  receive_thread.wait_for(1ms);
}

raw_connection::~raw_connection()
{
  exit_flag = true;
}


void raw_connection::ReceiveThread()
{
  const auto first_part_size = message_header::raw_byte_size + 4;
  vector<byte> header;
  header.resize(first_part_size);

  auto PayloadSize = [&header]()
  {
    if (header.size() < 4)
      throw "something wrong with header buffer";
    auto offset = header.size() - 4;
    auto calculated_size = *(int *)&header[offset];
    return calculated_size;
  };

  bool read_header_state = true;

  while (!exit_flag)
  {
    this_thread::sleep_for(10ms);
    if (exit_flag)
      break;

    auto raii = mutex_handler.Lock();
    auto ready = handler->available();
    if (read_header_state)
    {
      if (ready < first_part_size)
        continue; // we ignore not complete messages

      cout << "Get message header!!!" << endl;

      read(*handler, boost::asio::buffer(header, first_part_size));
      read_header_state = false;
      ready = handler->available();
    }

    auto required_payload_size = PayloadSize();
    if (ready < required_payload_size)
      continue;

    raw_message sure;
    sure.Fill(message_header(&header[0]));
    sure.payload.resize(required_payload_size);
    read(*handler, boost::asio::buffer(sure.payload));

    read_header_state = true;

    cout << "Get full message!!! " << sure.event << endl;

    {
      auto raiilock = mutex_received.Lock();
      received.push_back(sure);
    }
  }
}

void connection::Send(raw_message &message)
{
  auto lock_handler = raw->mutex_handler.Lock();
  auto lock_send = raw->mutex_send.Lock();
  vector<byte> buf = message;
  raw->handler->send(boost::asio::buffer(buf));
}