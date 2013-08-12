#ifndef _ED_NAME_SERVER_H_
#define _ED_NAME_SERVER_H_

#include "name_type.h"
#include "dictionary.h"

namespace ed
{
  struct name_server
  {
    typedef dictionary::id_type id_type;
    typedef dictionary::word_type word_type;
  private:
    dictionary *books;
    void ValidateBookId( const NAME_TYPE nt ) const;
  public:
    name_server();
    ~name_server()
    {
      delete[] books;
    }
    dictionary &operator[]( const NAME_TYPE nt );
    const dictionary &operator[]( const NAME_TYPE nt ) const;
  };
};

#endif