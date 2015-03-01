#pragma once

#include <unordered_map>
#include <memory>
using namespace std;

template<typename T>
struct holder
{
  unique_ptr<T> payload;

  template<typename K>
  decltype(declval<T::operator[](K)>) operator[](K) const;
  template<typename K, typename C>
  C &operator()(K) const;
};

template<typename K, typename T>
struct container
{
  typedef holder<T> my_holder;
  unordered_map<K, my_holder> storage;

  my_holder operator[](K) const;
  T &operator()(K) const;
};

#include "message.h"

typedef vector<decltype(message_destination::module)> listener_instance;

typedef container<int, listener_instance> listener_struct;

typedef container<int, listener_struct> listeners_container;

typedef container<int, listeners_container> events_container;

typedef container<int, events_container> modules_container;

template<typename T>
template<typename K>
decltype(declval<T::operator[](K)>) holder<T>::operator[](K a) const
{
  if (payload)
    return *payload[a];
  T tmp;
  return tmp[a];
}


template<typename T>
template<typename K, typename C>
C &holder<T>::operator()(K a) const
{
  if (payload)
    return *payload(a);
  T tmp;
  return t(a);
}
