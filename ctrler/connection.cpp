#include "connection.h"

bool handler;

connection::operator bool() const
{
  return !disconnected;
}

connection::connection(bool _handler)
  : handler(_handler)
{

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