#pragma once

#include <unordered_map>
#include <memory>
using namespace std;

template<typename T>
struct holder
{
  shared_ptr<T> payload;

  operator bool() const
  {
    return !!payload;
  }

  template<typename K>
  auto operator[](K a) const
  {
    if (!*this)
      return (*payload)[a];
    T tmp;
    return tmp[a];
  }

  template<typename K, typename C>
  auto &operator()(K a) const
  {
    if (!*this)
      return (*payload)(a);
    T tmp;
    return t(a);
  }

  auto &operator*() const
  {
    return *payload;
  }
};
template<typename K
, typename T>
struct container
{
  typedef holder<T> my_holder;
  unordered_map<K, my_holder> storage;

  auto operator[](K a) const
  {
    auto &it = storage.find(a);
    if (it != storage.end())
      return it->second;
    return holder<T>();
  }

  auto operator()(K a)
  {
    auto &holder = storage[a];
    auto &holdee = holder.payload;
    holdee = make_shared<T>();

    return *holdee;
  }

  auto &begin() const
  {
    return storage.begin();
  }

  auto &end() const
  {
    return storage.end();
  }
};

#include <ed\structs\message.h>

// Array of listening modules
typedef vector<decltype(message_destination::module)> listener_instance;

// Find map of listen modules of one listen instance
typedef container<int, listener_instance> listeners_container;

// Find map of listen instances by event id
typedef container<int, listeners_container> events_container;

// Find map of events by module id
typedef container<int, events_container> modules_container;