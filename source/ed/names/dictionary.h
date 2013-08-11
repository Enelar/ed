#ifndef _ED_DICTIONARY_H_
#define _ED_DICTIONARY_H_

#include <vector>
#include <string>

namespace ed
{
  struct __declspec(dllexport) dictionary
  {
    typedef std::string word_type;
    typedef unsigned int id_type;
  private:
    std::vector<word_type> &data_base;
    static const id_type reserved_as_failure = -1;
    id_type SearchWord( word_type ) const;
  public:
    dictionary();
    ~dictionary();
    id_type RegisterWord( word_type );
    bool IsWordExist( word_type ) const;
  };
};

#endif