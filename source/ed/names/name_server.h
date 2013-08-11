#ifndef _ED_NAME_SERVER_H_
#define _ED_NAME_SERVER_H_

#include "name_type.h"
#include "dictionary.h"

namespace ed
{
  struct __declspec(dllexport) name_server
  {
    typedef dictionary::id_type id_type;
    typedef dictionary::word_type word_type;
  private:
    dictionary books[COUNT];
    void ValidateBookId( const NAME_TYPE nt ) const;
  public:
    name_server();
    dictionary &operator[]( const NAME_TYPE nt );
    const dictionary &operator[]( const NAME_TYPE nt ) const;
  };
};

#endif