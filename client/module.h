#pragma once

#include <ed/structs/message.h>
#include <ed/structs/vocabulary.h>

class module
{
  int global_module_id;
  vocabulary<int> modules, events; // per interface translation

public:
  module(string module_name);

  void Emit(raw_message);
  void Emit(int event, vector<byte> payload = {});
  void Emit(int event, int module, vector<byte> payload = {});
  void Emit(int event, int module, int instance, vector<byte> payload = {});

  int RegisterEventName(string name, int local_id = 0);
  int RegisterModuleName(string name, int local_id = 0);
};
