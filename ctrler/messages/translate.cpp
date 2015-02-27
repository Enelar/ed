#include "translate.h"

messages::translate_message::translate_message(raw_message &that)
{
  auto *buf = &that.payload[0];
  copy((char *)buf, (char *)buf + that.payload.size(), name.begin());
}