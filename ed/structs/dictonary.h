#pragma once

#include <unordered_map>
#include <string>

using namespace std;

struct dictonary
{
  typedef int K;
  typedef string T; 

  int next_free = 1;
  unordered_map<T, K> a;
  unordered_map<K, T> b;

  void Insert(K, T);
  K Add(T);
  K operator[](T) const;
  T operator[](K) const;

  struct unknown {};
  struct already_known {};
};