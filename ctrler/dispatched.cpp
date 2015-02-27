#include "dispatcher.h"

dispatcher::dispatcher(ctrler &that)
  : target(that)
{

}

#include "messages\translate.h"
void dispatcher::Translate(raw_message &gift)
{
  messages::translate message(gift);
}

void dispatcher::Listen(raw_message &)
{

}

void dispatcher::Up(raw_message &)
{

}