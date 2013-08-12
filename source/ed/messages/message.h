#ifndef _ED_MESSAGES_MESSAGE_H_
#define _ED_MESSAGES_MESSAGE_H_

#include "../def.h"
#include "../exceptions/exception.h"
#include "../notifications/event_types.h"

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

    buffer( const std::string &m ) : len(m.length()), buf(NEW unsigned char[len])
    {
      memcpy(buf, m.c_str(), len);
    }

    operator std::string() const
    {
      char *t = new char[len + 1];
      memcpy(t, buf, len);
      t[len] = 0;
      std::string ret = t;
      delete[] t;
      return ret;
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

  struct __declspec(dllexport) message_flags
  {
    unsigned int size_length;
    EVENT_RING ring;
    EVENT_STATE state;

    message_flags( )
    {
      size_length = 0;
      ring = RING3_WORLD;
      state = POST_COMMIT;
    }

    message_flags( const flag_byte &b )
    {
      size_length = b.size_length;
      ring = (EVENT_RING)b.ring;
      state = (EVENT_STATE)b.state;
    }

    operator flag_byte()
    {
      flag_byte ret;
      ret.size_length = size_length;
      ret.ring = ring;
      ret.state = state;
      return ret;
    }
  };

  struct __declspec(dllexport) message
  {
    typedef unsigned char byte;
    typedef unsigned short word;

    mutable message_flags flags;
    byte dest;
    mutable word size; // opt
    word event;
    byte module;
    word instance;
    buffer *payload;

    message( int payload_size );
    message( const buffer & );
    operator buffer() const;
    message( const message & );
    message &operator=( const message & );
    ~message();

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
      if (payload)
        return payload->len;
      return 0;
    }

    int MessageSize() const;
    bool Completed() const;
    int ExpectedPayloadSize() const;
  private:
    int OffsetToEventSegment() const;
    int SizeLength( ) const;
  };
};

#endif