#pragma once

#include "vocabulary.h"

template<typename T, typename K>
auto vocabulary<T, K>::Add(T k) -> K
{
  auto &it = _a.find(k);
  if (it != _a.end())
    return it->second;

  while (_b.find(next_free) == _b.end())
    next_free++;

  auto id = next_free++;
  Insert(id, k);
  return id;
}

template<typename T, typename K>
auto vocabulary<T, K>::Global2Local(T k) const -> K
{
  auto &it = _a.find(k);
  if (it == _a.end())
    throw unknown();
  return it->second;
}

template<typename T, typename K>
auto vocabulary<T, K>::Local2Global(K k) const -> T
{
  auto &it = _b.find(k);
  if (it == _b.end())
    throw unknown();
  return it->second;
}

template<typename T, typename K>
auto vocabulary<T, K>::Insert(K k, T t) -> void
{
  if (_b.find(k) != _b.end() || _a.find(t) != _a.end())
    throw already_known();
  _a.insert({ t, k });
  _b.insert({ k, t });
}

