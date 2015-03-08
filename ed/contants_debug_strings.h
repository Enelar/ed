#pragma once

#include <map>
#include <string>

namespace ed
{
  namespace reserved
  {
    typedef std::map<int, std::string> predefined_vocabulary;

    template<typename T>
    struct debug_string_struct
    {
      predefined_vocabulary &predefined;
      T &container;

      auto operator[](int i) -> std::string;
    };

    template<typename T>
    auto BaseDebugStrings(predefined_vocabulary &a, T &b)->debug_string_struct<T>
    {
      return{ a, b };
    }

    namespace instance
    {
      extern predefined_vocabulary _strings;
      template<typename T>
      auto DebugStrings(T &a)
      {
        return BaseDebugStrings(_strings, a);
      }
    };

    namespace module
    {
      extern predefined_vocabulary _strings;
      template<typename T>
      auto DebugStrings(T &a)
      {
        return BaseDebugStrings(_strings, a);
      }
    }
    namespace event
    {
      extern predefined_vocabulary _strings;
      template<typename T>
      auto DebugStrings(T &a)
      {
        return BaseDebugStrings(_strings, a);
      }
    };
  };
};

struct dictonary;
namespace ed
{
  namespace reserved
  {
    template<>
    auto debug_string_struct<dictonary>::operator[](int i)->std::string;

    template<typename T>
    auto debug_string_struct<T>::operator[](int i)->std::string
    {
      {
        auto it = predefined.find(i);
        if (it != predefined.end())
          return it->second;
      }

      {
        auto it = container.find(i);
        if (it != container.end())
          return it->second;
      }

      return "<NULL>";
    }
  };
};