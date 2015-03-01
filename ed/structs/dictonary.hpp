#pragma once

#include "dictonary.h"

auto dictonary::Add(T k) -> K
{
  auto &it = a.find(k);
  if (it != a.end())
    return it->second;
  
  while (b.find(next_free) == b.end())
    next_free++;

  auto id = next_free++;
  Insert(id, k);
  return id;
}

auto dictonary::operator[](T k) const -> K
{
  auto &it = a.find(k);
  if (it == a.end())
    throw unknown();
  return it->second;
}

auto dictonary::operator[](K k) const -> T
{
  auto &it = b.find(k);
  if (it == b.end())
    throw unknown();
  return it->second;
}

auto dictonary::Insert(K k, T t) -> void
{
  if (b.find(k) != b.end() || a.find(t) != a.end())
    throw already_known();
  a.insert({ t, k });
  b.insert({ k, t });
}
