#ifndef _ED_MESSAGES_MESSAGE_H_
#define _ED_MESSAGES_MESSAGE_H_

#include "../def.h"
#include "../exceptions/exception.h"

namespace ed
{
  enum MESSAGE_TYPE
  {
    REGISTER,
    LISTEN,
    NOTIFY
  };
  struct message
  {
    const int len;
    unsigned char *buffer;
    
    message() : len(0), buffer(NULL)
    {
    }

    message( int _len ) : len(_len), buffer(NEW unsigned char[_len])
    {
    }

    message( const message &m ) : len(m.len), buffer(NEW unsigned char[len])
    {
      memcpy(buffer, m.buffer, len);
    }

    MESSAGE_TYPE GetType() const
    {
      throw_assert(len > 0);
      throw_assert(buffer);
      int t = buffer[0];
      throw_assert(t >= REGISTER && t <= NOTIFY);
      return (MESSAGE_TYPE)t;
    }

    ~message()
    {
      if (buffer)
        delete buffer;
    }
  private:
    void operator=( const message & );
  };
};

#endif