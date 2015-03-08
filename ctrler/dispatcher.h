#pragma once

#include <ed\structs\message.h>          
#include "containers.h"

class ctrler;

class dispatcher
{
  ctrler &target;
public:
  dispatcher(ctrler &);

  void Translate(raw_message &);
  void Listen(raw_message &);
  void Up(raw_message &);
  void Transmit(raw_message &);
  void TransmitHelper(modules_container &, raw_message &, bool broadcast = false);
};
