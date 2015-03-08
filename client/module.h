#pragma once

#include <ed/structs/message.h>
#include <ed/structs/vocabulary.h>
#include <ed/translation_hook.h>
#include "handle_adapter.h"
#include <memory>

class module
{
protected:
  int global_module_id = ed::reserved::module::BROADCAST;
  vocabulary<int> modules, events; // per interface translation

public:
  module(string module_name);
  virtual ~module();

  void Emit(raw_message);
  void Emit(int event, vector<byte> payload = {});
  void Emit(int event, int module, vector<byte> payload = {});
  void Emit(int event, int module, int instance, vector<byte> payload = {});

  int RegisterEventName(string name, int local_id = -1);
  int RegisterModuleName(string name, int local_id = -1);

  message_destination MyLocation() const;

  string EventNameLookup(int local_id);
  string ModuleNameLookup(int local_id);

  template<typename T, typename MODULE>
  void Listen(
      void (MODULE::*)(T),
      ed::translator_hook_event event,
      ed::translator_hook_module module = ed::reserved::module::BROADCAST,
      ed::translator_hook_instance instance = ed::reserved::instance::BROADCAST);


  void OnMessage(raw_message);
private:
  // Step Four: Tell connector and ctrler
  void Listen(int event, int module, int intance);
  typedef shared_ptr<base_handle_adapter> handler_stored;
  vocabulary<int, handler_stored> callbacks;
};

#include "module.hpp"
