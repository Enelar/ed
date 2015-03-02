#pragma once

#include "vocabulary.h"

struct dictonary : vocabulary<string, int>
{
  auto operator[](int a) const
  {
    return Local2Global(a);
  }

  auto operator[](string a) const
  {
    return Global2Local(a);
  }
};