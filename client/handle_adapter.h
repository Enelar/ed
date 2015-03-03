#pragma once

#include <ed/structs/message.h>

struct base_handle_adapter
{
  virtual void operator()(raw_message) = 0;
};

template<typename MODULE, typename T>
struct handle_adapter : base_handle_adapter
{
  typedef void (MODULE::*handlerT)(T);    
  MODULE &m;
  handlerT handler;

  handle_adapter( MODULE &_m, handlerT _handler )
    : m(_m), handler(_handler)
  {}

  void operator()(raw_message obj) override
  {
    (m.*handler)(obj);
  }
};
