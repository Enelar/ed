#pragma once

#include <ed/structs/message.h>
#include <ed/structs/vocabulary.h>
#include "handle_adapter.h"
#include <memory>

class module
{
  int global_module_id = ed::reserved::module::BROADCAST;
  vocabulary<int> modules, events; // per interface translation

public:
  module(string module_name);
  virtual ~module();

  void Emit(raw_message);
  void Emit(int event, vector<byte> payload = {});
  void Emit(int event, int module, vector<byte> payload = {});
  void Emit(int event, int module, int instance, vector<byte> payload = {});

  int RegisterEventName(string name, int local_id = ed::reserved::event::BROADCAST);
  int RegisterModuleName(string name, int local_id = ed::reserved::module::BROADCAST);

  string EventNameLookup(int local_id);
  string ModuleNameLookup(int local_id);

  template<typename T, typename MODULE>
  void Listen(
    void (MODULE::*)(T),
    int event,
    int module = ed::reserved::module::BROADCAST,
    int instance = ed::reserved::instance::BROADCAST
    );

  void OnMessage(raw_message);
private:
  void Listen(int event, int module, int intance);
  typedef shared_ptr<base_handle_adapter> handler_stored;
  vocabulary<int, handler_stored> callbacks;
};

#include "module.hpp"
