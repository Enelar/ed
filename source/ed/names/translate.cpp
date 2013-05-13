#include "translate.h"
#include "../exceptions/exception.h"

using namespace ed;

int translate::SearchId( pair::member_pointer mp, id_type value ) const
{
  int i = 0, s = db.size();
  for (; i < s; ++i)
    if (db[i].*mp == value)
      return i;
  return failure_pair_id;
}

const translate::pair &translate::SearchPair( pair::member_pointer mp, id_type value ) const
{
  int ret = SearchId(mp, value);
  throw_sassert(ret != failure_pair_id, "Pair not found");
  return db[ret];
}

void translate::AddPair( id_type local, id_type global )
{
  if (SearchId(&pair::local, local) != failure_pair_id)
    throw_message("Local id already exists");
  if (SearchId(&pair::global, global) != failure_pair_id)
    throw_message("Local id already exists");

  int id = db.size();
  db.push_back(pair());
  db[id].local = local;
  db[id].global = global;
}

translate::id_type translate::ToLocal( id_type global ) const
{
  const pair &result = SearchPair(&pair::global, global);
  return result.local;
}

translate::id_type translate::ToGlobal( id_type local ) const
{
  const pair &result = SearchPair(&pair::local, local);
  return result.global;
}
