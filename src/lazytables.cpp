/*
 * lazydata.cpp
 *
 *  Created on: Aug 29, 2011
 *      Author: patrick
 */
#include "lazytables.hpp"
#include "helpers.hpp"

#include "include/macros.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


using namespace Helpers::LazyTables;

   TVoid
TLazyTables::updateTableInfo
   (
   TBoolean add,
   Tnc8 *table_col,
   TBaseIndex index
   )
   {
   /* if this column belongs to a table */
   Tnc8 *col = ComputeColumnName(table_col);
   Tnc8 *table = ComputeTableName(table_col);

//   TRACE_STR(table);
//   TRACE_STR(col);
//   END_LINE;
   
   addColumn(col, table);

   /* if this table exists */
   if(m_tableInfoMap.count(table))
      {
      if(add)
         m_tableInfoMap[table].validIndexes.insert(index);
      else
         m_tableInfoMap[table].validIndexes.erase(index);
      }
   }

   TLazyTables &
TLazyTables::self()
   {
   return *this;
   }
   
   size_t
TLazyTables::countRows
   (
   Tnc8 *table
   )
   {
   if(table && m_tableInfoMap.count(table))
      return m_tableInfoMap[table].validIndexes.size();

   return 0;
   }

   TBoolean
TLazyTables::hasRow
   (
   Tnc8 *table,
   TBaseIndex index
   )
   {
   return table && m_tableInfoMap.count(table) &&
      m_tableInfoMap[table].validIndexes.count(index);
   }
   
  TBaseIndex
TLazyTables::begin
  (
  Tnc8 *table
  )
  {
  if(table && m_tableInfoMap.count(table))
    {
    return *m_tableInfoMap[table].validIndexes.begin();
    }
  LOG_WARNING("There's is no \"%s\" table.\n", table);
  return 0;
  }

   TBaseIndex
TLazyTables::next
   (
   Tnc8 *table,
   TBaseIndex index
   )
   {
   if(table && m_tableInfoMap.count(table))
      {
      std::set<TBaseIndex>::iterator i = m_tableInfoMap[table].validIndexes.find(index);
      if(i != --m_tableInfoMap[table].validIndexes.end())
         return *(++i);
      else
         {
         return index+1; // return one greater than last row index
         }
      }
   LOG_WARNING("There's is no \"%s\" table.\n", table);
   return 0;
   }

  TBaseIndex
TLazyTables::end
   (
   Tnc8 *table
   )
   {
   if(table && m_tableInfoMap.count(table))
      {
      std::set<TBaseIndex>::reverse_iterator i = m_tableInfoMap[table].validIndexes.rbegin();
      return (*i)+1;
      }
   LOG_WARNING("There's is no \"%s\" table.\n", table);
   return 0;
   }

   TBaseIndex 
TLazyTables::getUnusedIndex
   (
   Tnc8 *table
   )
   {
//   std::set<TBaseIndex>::iterator i;
//   std::set<TBaseIndex> &validIndex = m_tableInfoMap[table];
//   TBaseIndex prev = 0;
//   
//   for(
//      i = validIndexes.begin();
//      i != validIndexes.end();
//      prev = (*i), i++
//      )
//      {
//      if((*i) && (*i) - 1 > prev)
//         return *i;
//      }
//   return (*i)+1;
   return end(table);
   }

  
   TBoolean
TLazyTables::hasColumn
   (
   Tnc8 *table_col
   )
   {
   if(table_col)
      {
      Tnc8 *table = ComputeTableName(table_col);
      Tnc8 *col = ComputeColumnName(table_col);
      return m_tableInfoMap.count(table) &&
            m_tableInfoMap[table].colset.count(col);
      }
   return FALSE;
   }


/*
 * May also create the table if it doesn't exist yet.
 */
   TVoid
TLazyTables::addColumn
   (
   Tnc8 *col,
   Tnc8 *table
   )
   {
   if(table && col)
      {
      /* Make this column mappable to this table */
      m_colOwnerMap[col] = table;
      /* Set default table info values */
      /* add this column to the table's list of columns */
      m_tableInfoMap[table].colset.insert(col);
      }
   }

   TBoolean
TLazyTables::hasRecord
   (
   Tnc8 *table_col,
   TBaseIndex index
   )
   {
   /* true of column exists and
    * this index is a key for this column
    */
   return table_col && m_recordMap.count(table_col) &&
         m_recordMap[table_col].count(index);
   }

   TBoolean
TLazyTables::hasInteger
   (
   Tnc8 *table_col,
   TBaseIndex index
   )
   {
   /* true if the column has this record and its an integer */
   return hasRecord(table_col, index) &&
         m_recordMap[table_col][index].isInteger;
   }

   TBoolean
TLazyTables::hasString
   (
   Tnc8 *table_col,
   TBaseIndex index
   )
   {
   /* true if the column has this record and its not an integer */
   return hasRecord(table_col, index) &&
         !m_recordMap[table_col][index].isInteger;
   }

   Ts64
TLazyTables::getInteger
   (
   Tnc8 *table_col,
   TBaseIndex index
   )
   {
   if(hasInteger(table_col, index))
      return m_recordMap[table_col][index].value.integer;

   printf("%s: WARNING: The requested integer does not exist! %s."FRMT_INT_IDX"\n", __FUNCTION__, table_col, index);
   return 0;
   }

   Tnc8*
TLazyTables::getString
   (
   Tnc8 *table_col,
   TBaseIndex index
   )
   {
   if(hasString(table_col, index))
      return m_recordMap[table_col][index].value.str.c_str();

   printf("%s: WARNING: The requested string does not exist! %s."FRMT_INT_IDX"\n", __FUNCTION__, table_col, index);
   return NULL;
   }

   TVoid
TLazyTables::setInteger
   (
   Tnc8 *table_col,
   TBaseIndex index,
   Ts64 value
   )
   {
   if(table_col)
      {
//      printf("setting integer %s.%u = %lld\n", table_col, index, value);
      m_recordMap[table_col][index].value.integer = value;
      m_recordMap[table_col][index].isInteger = TRUE;
      updateTableInfo(TRUE, table_col, index);
      }
   }

   TVoid
TLazyTables::setString
   (
   Tnc8 *table_col,
   TBaseIndex index,
   Tnc8 *value
   )
   {
   if(table_col)
      {
//      printf("TLazyTables::setString: setting string %s.%u = \"%s\"\n", table_col, index, value);
      m_recordMap[table_col][index].value.str = value;
      m_recordMap[table_col][index].isInteger = FALSE;
      updateTableInfo(TRUE, table_col, index);
      }
   }

   TVoid
TLazyTables::setString
   (
   Tnc8 *table_col,
   TBaseIndex index,
   Tnc8 *value,
   size_t length
   )
   {
   if(table_col)
      {
      std::string s(value, length);
      setString(table_col, index, s.c_str());
//      printf("TLazyTables::setString: setting %s.%u = \"%s\"\n", table_col, index, s.c_str());
//      m_recordMap[table_col][index].value.str = s;
//      m_recordMap[table_col][index].isInteger = FALSE;
//      updateTableInfo(TRUE, table_col, index);
      }
   }

   TVoid
TLazyTables::deleteRecord
   (
   Tnc8 *table_col,
   TBaseIndex index
   )
   {
   if(hasRecord(table_col, index))
      {
//      printf("deleting %s.%u\n", table_col, index);
      m_recordMap[table_col].erase(index);
      updateTableInfo(FALSE, table_col, index);
      }
   }
