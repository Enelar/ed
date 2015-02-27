#pragma once

#include <unordered_map>
#include <string>

using namespace std;

struct dictonary
{
  int next_free = 1;
  unordered_map<string, int> a;
  unordered_map<int, string> b;

  int Add(string);
  int operator[](string) const;
  string operator[](int) const;
};