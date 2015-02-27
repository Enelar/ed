#pragma once

#include "message.h"

class ctrler;

class dispatcher
{
  ctrler &target;
public:
  dispatcher(ctrler &);

  void Translate(raw_message &);
  void Listen(raw_message &);
  void Up(raw_message &);
};
