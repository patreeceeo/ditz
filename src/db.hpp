// Include this file wherever you want to use the database implemented
// in this folder.

#ifndef DB_HPP
#define DB_HPP

#include "lazytables.hpp"
#include "helpers.hpp"

namespace Data
   {
   using namespace Helpers::LazyTables;
   typedef TLazyTables TBase;
   }

#endif
