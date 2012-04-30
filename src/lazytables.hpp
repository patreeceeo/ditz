/*
 * lazydata.hpp
 *
 * A simple, general purpose tabular data storage class which could serve as
 * the basis for a database.
 *  Created on: Aug 29, 2011
 *      Author: patrick
 */

#ifndef LAZYTABLES_HPP_
#define LAZYTABLES_HPP_

#include <map>
#include <string>
#include <set>

#include "include/aditypes.h"
#include "include/types.h"

class TLazyTables
   {
   std::string s_sTableColumnAggregate;
   std::string s_sTableName;
   std::string s_sColumnName;

   struct TRecord
      {
      struct
         {
         Ts64 integer;
         std::string str;
         }value;
      TBoolean isInteger;
      };

   struct TTableInfo
      {
      std::set<std::string> colset;
      std::set<TBaseIndex> validIndexes;
      };
   /* maps "table:column" names to sparse list of records */
   std::map<std::string, std::map<TBaseIndex, TRecord> >   m_recordMap;
   /* maps table names to table info */
   std::map<std::string, TTableInfo> m_tableInfoMap;
   /* maps column names to table names */
   std::map<std::string, std::string> m_colOwnerMap;

   TVoid updateTableInfo(TBoolean add, Tnc8 *col, TBaseIndex index);

   public:
      TLazyTables &self();
      size_t countRows (Tnc8 *table);
      TBoolean hasRow (Tnc8 *table, TBaseIndex);
      TBaseIndex begin (Tnc8 *table);
      TBaseIndex next (Tnc8 *table, TBaseIndex);
      TBaseIndex end (Tnc8 *table);
      TBaseIndex getUnusedIndex(Tnc8 *table);
      TBoolean hasColumn (Tnc8 *table_col);
      TVoid addColumn (Tnc8 *col, Tnc8 *table);
      TBoolean hasRecord (Tnc8 *table_col, TBaseIndex);
      TBoolean hasInteger (Tnc8 *table_col, TBaseIndex);
      TBoolean hasString (Tnc8 *table_col, TBaseIndex);
      Ts64 getInteger (Tnc8 *table_col, TBaseIndex);
      Tnc8* getString (Tnc8 *table_col, TBaseIndex);
      TVoid setInteger (Tnc8 *table_col, TBaseIndex, Ts64 value);
      TVoid setString (Tnc8 *table_col, TBaseIndex, Tnc8 *value);
      TVoid setString (Tnc8 *table_col, TBaseIndex, Tnc8 *value, size_t length);
      TVoid deleteRecord (Tnc8 *table_col, TBaseIndex);
   };
#endif /* LAZYTABLES_HPP_ */
