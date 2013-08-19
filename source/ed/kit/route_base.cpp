#include "route_base.h"

using namespace ed;

route_base::route_base( const buffer &m )
  : mes(m)
{
}

const buffer &route_base::MessageToSend() const
{
  return mes;
}

// parsing

#define COUNT_SIZE (sizeof(int))
#define ADDRESS_SIZE (sizeof(int) * 2)

route_base::operator message() const
{
  int
    head_size = COUNT_SIZE + ADDRESS_SIZE * marked.size(),
    size = head_size +  mes.len;
  buffer *res = NEW buffer(size);
  memcpy(res->buf, mes.buf + head_size, mes.len); // copy original message

  int *p = (int *)res->buf;
  *p++ = marked.size();

  std::set<slot_data::listener>::const_iterator i = marked.begin(), e = marked.end();
  while (i != e)
  {
    const slot_data::listener t = *i;
    *p++ = t.instance;
    *p++ = t.module;
    i++;
  }
  // routes succesfully writed
  message ret(mes);
  delete ret.payload;
  ret.payload = res;
  return ret;
}

route_base::route_base( const message &m )
  : mes(EstimatedBufferSizeOnParse(m))
{
  ExtractPayloadOnParse(m);
  // Addresses not first, because payload parsing has certain asserts checks.
  ExtractAddresesOnParse(m);
}

int route_base::EstimatedBufferSizeOnParse( const message &m ) const
{
  int addresses_size = PayloadPosOnParse(m);
  int min_required_size = addresses_size + m.MinRequiredSize();
  throw_assert(m.PayloadSize() > min_required_size);
  int ret = m.PayloadSize() - addresses_size;
  throw_assert(ret > 0);
  return ret;
}

int route_base::PayloadPosOnParse( const message &m ) const
{
  throw_assert(m.PayloadSize() > COUNT_SIZE + m.MinRequiredSize());
  const buffer &b = *m.payload;
  int count = *(int *)b.buf;
  int addresses_size = COUNT_SIZE + ADDRESS_SIZE *count;
  return addresses_size;
}

void route_base::ExtractPayloadOnParse( const message &m )
{
  int offset = PayloadPosOnParse(m);
  throw_assert(mes.len == m.payload->len - offset);
  memcpy(mes.buf, m.payload->buf + offset, mes.len);
}

void route_base::ExtractAddresesOnParse( const message &m )
{
  const buffer &b = *m.payload;
  int *p = (int *)b.buf;
  int count = *p++;

  slot_data::listener t;
  for (int i = 0; i < count; i++)
  {
    t.instance = *p++;
    t.module = *p++;
    marked.insert(t);
  }
}