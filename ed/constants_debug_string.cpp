#include "contants_debug_strings.h"
#include "structs\constants.h"

using namespace ed::reserved;

predefined_vocabulary instance::_strings;
predefined_vocabulary module::_strings;
predefined_vocabulary event::_strings;

#define QUOTEME(x) #x
#define TOSTRING(x) QUOTEME(x)
#define ENUM_TO_PAIR(name) {name, TOSTRING(name)}

namespace
{
  struct set_predefined_strings_obj
  {
    set_predefined_strings_obj()
    {
      {
        using namespace instance;
        _strings.insert(ENUM_TO_PAIR(BROADCAST));
        _strings.insert(ENUM_TO_PAIR(MASTER));
        _strings.insert(ENUM_TO_PAIR(CONTROLLER));
      }

      {
        using namespace module;
        _strings.insert(ENUM_TO_PAIR(BROADCAST));
        _strings.insert(ENUM_TO_PAIR(HEART_BEAT));
        _strings.insert(ENUM_TO_PAIR(NAMES));
        _strings.insert(ENUM_TO_PAIR(ME));
        _strings.insert(ENUM_TO_PAIR(LISTEN));
      }

      {
        using namespace event;
        _strings.insert(ENUM_TO_PAIR(BROADCAST));
        _strings.insert(ENUM_TO_PAIR(INSTANCE_UP));
        _strings.insert(ENUM_TO_PAIR(MODULE_UP));
        _strings.insert(ENUM_TO_PAIR(LISTEN));
        _strings.insert(ENUM_TO_PAIR(DIRECT_SEND));
        _strings.insert(ENUM_TO_PAIR(EXCLUSIVE_SEND));
        _strings.insert(ENUM_TO_PAIR(MODULE_NAME_LOOKUP));
        _strings.insert(ENUM_TO_PAIR(EVENT_NAME_LOOKUP));
        _strings.insert(ENUM_TO_PAIR(MODULE_GLOBAL_ID_REQUEST));
        _strings.insert(ENUM_TO_PAIR(EVENT_GLOBAL_ID_REQUEST));
        _strings.insert(ENUM_TO_PAIR(INSTANCE_DOWN));
        _strings.insert(ENUM_TO_PAIR(MODULE_DOWN));
      }
    }
  } _tmp;
}

#include "structs\dictonary.h"
template<>
auto debug_string_struct<::dictonary>::operator[](int i)->std::string
{
  {
    auto it = predefined.find(i);
    if (it != predefined.end())
      return it->second;
  }

  try
  {
    return container[i];
  }
  catch (dictonary::unknown &)
  {
    return "<NULL>";
  }
}