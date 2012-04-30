#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lazytables.hpp"
#include "helpers.hpp"
#include "include/macros.h"

namespace Helpers
  {
  namespace LazyTables
    {
           Tnc8 *
    ComputeTableName
       (
       Tnc8 *table_col
       )
       {
       if(table_col)
          {
          if(strchr(table_col, ':'))
             {
             std::ptrdiff_t iSplit = index(table_col, ':') - table_col;
             Tn8 *table = (Tn8*)malloc(iSplit + 1);
             strncpy(table, table_col, iSplit);
             table[iSplit] = '\0';
             return table;
             }
          return table_col;
          }
       LOG_WARNING("table_col is NULL");
       return "error";
       }
    
    
       Tnc8 *
    ComputeColumnName
       (
       Tnc8 *table_col
       )
       {
       if(table_col)
          {
          if(strchr(table_col, ':'))
             {
             std::ptrdiff_t iSplit = index(table_col, ':') - table_col;
             size_t lCol = strlen(table_col) - iSplit - 1;
             Tn8 *col = (Tn8*)malloc(lCol + 1);
             strncpy(col, table_col+iSplit+1, lCol);
             col[lCol] = '\0';
             return col;
             }
          return table_col;
          }
       LOG_WARNING("table_col is NULL");
       return "error";
       }
    
    
       Tnc8 *
    ComputeTableColumnAggregate
       (
       Tnc8 *table,
       Tnc8 *col
       )
       {
       if(col)
          {
          if(table)
             {
             size_t lTable_col = strlen(table) + strlen(col) + 1; // +1 for ':'
             Tn8* table_col = (Tn8*)malloc(lTable_col + 1); //+1 for \0
             strcpy(table_col, table);
             strcat(table_col, ":");
             strcat(table_col, col);
             return table_col;
             }
          else
             LOG_WARNING("table is NULL");
          }
       LOG_WARNING("col is NULL");       
       }
    
    
      TBoolean 
    HasColumn 
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      return lt.hasColumn(table_col);
      }
      
      TBoolean 
    HasRecord 
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      TBaseIndex index
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      return lt.hasRecord(table_col, index);
      }
      
      TBoolean 
    HasInteger 
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      TBaseIndex index
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      return lt.hasInteger(table_col, index);      
      }
      
      TBoolean 
    HasString 
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      TBaseIndex index
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      return lt.hasString(table_col, index);
      }

      Ts64 
    GetInteger 
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      TBaseIndex index
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      return lt.getInteger(table_col, index);      
      }

      Tnc8 *
    GetString 
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      TBaseIndex index
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      return lt.getString(table_col, index);      
      }

      TVoid 
    SetInteger 
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      TBaseIndex index,
      Ts64 integer
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      lt.setInteger(table_col, index, integer);
      }

      TVoid 
    SetString 
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      TBaseIndex index,
      Tnc8 *str
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      lt.setString(table_col, index, str);
      }

      TVoid
    SetString
      (
      TLazyTables &lt,
      Tnc8 *table,
      Tnc8 *col,
      TBaseIndex index,
      Tnc8 *str,
      size_t length
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      lt.setString(table_col, index, str, length);
      }

      TVoid 
    DeleteRecord 
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      TBaseIndex index
      )
      {
      Tnc8 *table_col = ComputeTableColumnAggregate(table, col);
      lt.deleteRecord(table_col, index);
      }
      
      TBoolean 
    ColumnHasString
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      Tnc8 *str
      )
      {
      TBaseIndex index;
      for_each_row(lt, table, index)
        {
        Tnc8 *dbstr = GetString(lt, table, col, index);
        if(str && dbstr)
           {
           if(strcmp(dbstr, str) == 0)
              return TRUE;
           }
        }
      return FALSE;
      }
    
      TBoolean 
    ColumnHasInteger
      (
      TLazyTables &lt, 
      Tnc8 *table, 
      Tnc8 *col, 
      Ts64 integer
      )
      {
      TBaseIndex index;
      for_each_row(lt, table, index)
        {
        if(GetInteger(lt, table, col, index) == integer)
          return TRUE;
        }
      return FALSE;
      }

    }
  }
