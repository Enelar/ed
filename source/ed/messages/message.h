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
  struct buffer
  {
    const int len;
    unsigned char *buf;

    buffer() : len(0), buf(NULL)
    {
    }

    buffer( int _len ) : len(_len), buf(NEW unsigned char[_len])
    {
    }

    buffer( const buffer &m ) : len(m.len), buf(NEW unsigned char[len])
    {
      memcpy(buf, m.buf, len);
    }

    ~buffer()
    {
      if (buf)
        delete buf;
    }
  private:
    void operator=( const buffer & );
  };

  struct flag_byte
  {
    unsigned size_length : 2;
    unsigned : 1;
    unsigned ring : 2;
    unsigned state : 2;
    unsigned : 1;
  };

  struct message
  {
    typedef unsigned char byte;
    typedef unsigned short word;

    flag_byte flags;
    byte dest;
    word size; // opt
    word event;
    byte module;
    word instance;
    buffer *payload;

    message( const buffer & );
    operator buffer() const;

    static int MinRequiredSize()
    {
      return
        sizeof(byte) +
        sizeof(byte) +
        sizeof(word) +
        sizeof(byte) +
        sizeof(word);
    }
    
    static int ExpectedSize( flag_byte flag )
    {
      throw_assert(flag.size_length != 3);
      return MinRequiredSize() + flag.size_length;
    }

    word PayloadSize() const
    {
      return size;
    }
  };
};

#endif