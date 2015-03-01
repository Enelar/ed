#include "dictonary.h"

int dictonary::Add(string k)
{
  auto &it = a.find(k);
  if (it != a.end())
    return it->second;
  auto id = next_free++;
  a.insert({ k, id });
  b.insert({ id, k });
  return id;
}

int dictonary::operator[](string k) const
{
  auto &it = a.find(k);
  if (it == a.end())
    throw unknown();
  return it->second;
}

string dictonary::operator[](int k) const
{
  auto &it = b.find(k);
  if (it == b.end())
    throw unknown();
  return it->second;
}