#pragma once
#include "structs\constants.h"

namespace ed
{
  template<typename T>
  struct translator_hook
  {
    union
    {
      int local_id;
      T global_id;
    };
    bool is_local;

    translator_hook(int _local_id)
      : local_id(_local_id), is_local(true)
    {

    }

    translator_hook(T _global_id)
      : global_id(_global_id), is_local(false)
    {

    }

    operator int &()
    {
      return local_id;
    }
  };

  typedef translator_hook<reserved::event::EVENT> translator_hook_event;
  typedef translator_hook<reserved::module::MODULE> translator_hook_module;
  typedef translator_hook<reserved::instance::INSTANCE> translator_hook_instance;
}
