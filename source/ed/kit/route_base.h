#ifndef _ED_KIT_ROUTE_BASE_H_
#define _ED_KIT_ROUTE_BASE_H_

#include "../notifications/event_notification.h"
#include "../notifications/listener.h"
#include <set>

namespace ed
{
  struct route_base
  {
    buffer mes;
  public:
    route_base( const buffer &construct_route );

    route_base( const message &parse_route );
    operator message() const;

    const buffer &MessageToSend() const;

    std::set<slot_data::listener> marked;

  private:
    int PayloadPosOnParse( const message & ) const;
    int EstimatedBufferSizeOnParse( const message & ) const;
    void ExtractPayloadOnParse( const message & );
    void ExtractAddresesOnParse( const message & );
  };

  struct direct_send : route_base
  {
  };

  struct exclusive_send : route_base
  {
  };
};

#endif