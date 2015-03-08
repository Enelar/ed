#pragma once

#include <ed/structs/message.h>
#include <ed/structs/vocabulary.h>
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

  // Step One: Translate local module ID to global
  template<typename T, typename MODULE, typename eventT = int>
  void Listen(void (MODULE::*)(T), eventT event,
    int module, int instance = ed::reserved::instance::BROADCAST);

  // Step Two: Translate local event ID to global
  template<typename T, typename MODULE>
  void Listen(void (MODULE::*)(T), int event, 
    ed::reserved::module::MODULE module = ed::reserved::module::BROADCAST, int instance = ed::reserved::instance::BROADCAST);

  // Step Three: Store and tell connector
  template<typename T, typename MODULE>
  void Listen(void (MODULE::*)(T), ed::reserved::event::EVENT event, ed::reserved::module::MODULE module, int instance = ed::reserved::instance::BROADCAST);




  void OnMessage(raw_message);
private:
  void Listen(int event, int module, int intance);
  typedef shared_ptr<base_handle_adapter> handler_stored;
  vocabulary<int, handler_stored> callbacks;
};

#include "module.hpp"
