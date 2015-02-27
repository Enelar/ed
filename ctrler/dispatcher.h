#pragma once

#include "message.h"

class ctrler;

class dispatcher
{
  ctrler &target;
public:
  dispatcher(ctrler &);

  void Translate(raw_message &);
};
