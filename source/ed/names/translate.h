/* This file protected by faith_base_00 license
 * No part of this file could be copyed or changed without Kirill Berezin agreement
 * No part of this file could be used or viewed without Kirill Berezin agreement
 */

#ifndef _ED_TRANSLATE_H_
#define _ED_TRANSLATE_H_

#include <vector>

namespace ed
{
  struct translate
  {
    typedef unsigned int id_type;
  private:
    struct pair
    {
      id_type local, global;
      typedef id_type pair::* member_pointer;
    };
    std::vector<pair> db;
    static const int failure_pair_id = -1;
    int SearchId( pair::member_pointer mp, id_type value ) const;
    const pair &SearchPair( pair::member_pointer mp, id_type value ) const;
  public:
    void AddPair( id_type local, id_type global );
    id_type ToLocal( id_type global ) const;
    id_type ToGlobal( id_type local ) const;
  };
};

#endif
