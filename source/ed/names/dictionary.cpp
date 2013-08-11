#include "../def.h"
#include "dictionary.h"

using namespace ed;

dictionary::id_type dictionary::SearchWord( word_type word ) const
{
  id_type i = 0, s = data_base.size();
  for (;i < s; ++i)
    if (data_base[i] == word)
      return i;
  return reserved_as_failure;
}

dictionary::id_type dictionary::RegisterWord( word_type word )
{
  id_type ret = SearchWord(word);
  if (ret == reserved_as_failure)
  {
    data_base.push_back(word);
    ret = data_base.size() - 1;
  }
  return ret;
}

bool dictionary::IsWordExist( word_type word ) const
{
  return SearchWord(word) != reserved_as_failure;
}

dictionary::dictionary()
  : data_base(*NEW std::vector<word_type>())
{
}

dictionary::~dictionary()
{
  delete &data_base;
}