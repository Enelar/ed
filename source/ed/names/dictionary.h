/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_DICTIONARY_H_
#define _ED_DICTIONARY_H_

#include <vector>
#include <string>

namespace ed
{
  struct dictionary
  {
    typedef std::string word_type;
    typedef unsigned int id_type;
  private:
    std::vector<word_type> data_base;
    static const id_type reserved_as_failure = -1;
    id_type SearchWord( word_type ) const;
  public:
    id_type RegisterWord( word_type );
    bool IsWordExist( word_type ) const;
  };
};

#endif