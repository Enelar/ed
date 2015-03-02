#pragma once

#include <unordered_map>
#include <string>

using namespace std;

template<typename T, typename K = int>
struct vocabulary
{

  int next_free = 1;
  unordered_map<T, K> _a;
  unordered_map<K, T> _b;

  void Insert(K local, T global);
  K Add(T global);
  T Local2Global(K) const;
  K Global2Local(T) const;

  struct unknown {};
  struct already_known {};
};

#include "vocabulary.hpp"