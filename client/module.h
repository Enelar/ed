#pragma once

#include <ed/structs/message.h>
#include <ed/structs/vocabulary.h>

class module
{
  int global_module_id = ed::reserved::module::BROADCAST;
  vocabulary<int> modules, events; // per interface translation

public:
  module(string module_name);

  void Emit(raw_message);
  void Emit(int event, vector<byte> payload = {});
  void Emit(int event, int module, vector<byte> payload = {});
  void Emit(int event, int module, int instance, vector<byte> payload = {});

  int RegisterEventName(string name, int local_id = 0);
  int RegisterModuleName(string name, int local_id = 0);

  string EventNameLookup(int local_id);
  string ModuleNameLookup(int local_id);

  typedef void (module::*event_handler)(raw_message &);

  void Listen(
      event_handler,
      int event,
      int module = ed::reserved::module::BROADCAST,
      int instance = ed::reserved::instance::BROADCAST
      );

  template<typename T>
  void Listen(
    void (module::*)(message<T>),
    int event,
    int module = ed::reserved::module::BROADCAST,
    int instance = ed::reserved::instance::BROADCAST
    );
private:
  vocabulary<event_handler *> callbacks;
};

#include "module.hpp"
