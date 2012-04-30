#include "repl.hpp"

#include "parser.h"

#include "lazytables.hpp"
#include "helpers.hpp"
#include "index_adaptor.hpp"

#include "include/macros.h"

#undef SPACE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>

#include <string.h>
#include <math.h>

namespace readline
   {
   #include <readline/readline.h>
   #include <readline/history.h>
   }


#define TRUE_STRING "true"
#define FALSE_STRING "false"

using namespace Helpers::LazyTables;

typedef enum
   {
   LAYER_LAZYTABLES
   } TLayer;

//static TLazyTables g_internalMeta;
//static TLazyTables g_internalData;
static TLazyTables g_meta;
static TLazyTables g_data;
static TIndexAdaptor g_ia;
static TLayer g_layer = LAYER_LAZYTABLES;
static T16 g_radix = 10;
static std::string tempString;
static Tn8 g_shell_prompt[100];
static TBoolean g_freeInput;
static size_t g_inputIndex = 0;
static Tnc8 *g_input;
static TBoolean g_quit = FALSE;
static TBoolean g_echo = FALSE;

//TVoid
//ReplUseExternalBase(TLazyTables &db)
//   {
//   g_data = db;
//   }

//#ifdef __cplusplus
//extern "C" {
//#endif

   TLazyTables&
ReplGetDataReference()
   {
   return g_data;
   }

   TVoid 
Initialize_repl()
   {
   snprintf(g_shell_prompt, sizeof(g_shell_prompt), "%s@db > ", getenv("USER"));
   }


   TVoid
ReplDoHelp()
   {
   puts("Help                           - Print this help.");
   puts("Layer [<layer>]                - Get/Set current layer.");
   puts("Quit                           - Exit.");
   puts("Describe <entity>              - Print description of argued entity");
   puts("Print <entity>                 - Print the entity itself (whatever that means)");
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         puts("Has row <table> <index>        - Check for existence of entire row");
         puts("Has col <table>:<column>       - Check for existence of column in table");
         puts("Has <table>:<column> <index>   - Check if this record exists.");
         puts("Get <table>:<column> <index>   - Print value of record.");
         puts("Set <table>:<column> <index> <value> \n"
            "                                 - Set value of record.");
         puts("Delete <table>:<column> <index> - Delete this record.");
      }
   }

   TVoid
ReplSetInput
   (
   Tnc8 *input,
   TBoolean dynamic
   )
   {
   if(g_freeInput)
      free((void*)g_input);
   g_input = input;
   // adding the previous input into history
   readline::add_history(input);
   if(g_echo)
      printf("\"%s\"\n", input);
   g_freeInput = dynamic;
   g_inputIndex = 0;
   }
   
   TBoolean
ReplItsQuittingTime()
   {
   return g_quit;
   }

   TVoid
ReplDoPrompt()
   {
   Tnc8 *input;
   do
      {
      input = readline::readline(g_shell_prompt);
      if (!input)
         return;
      }
   while (strlen(input) == 0);
   
   ReplSetInput(input, TRUE);
   }

   TVoid 
ReplBeginQuit()
   {
   g_quit = TRUE;
   }

   
   TVoid
ReplDoQuit()
   {
   puts("Thank you come again!");
   exit(0);
   }

   TVoid
ReplSetLayer
   (
   Tnc8 *layerName
   )
   {
   if(strcmp(layerName, "lazytables") == 0)
      g_layer = LAYER_LAZYTABLES;
   }
   
   TVoid
ReplDoDescribe
   (
   Tnc8 *name
   )
   {
   if(name)
      {
      switch(g_layer)
         {
         case LAYER_LAZYTABLES:
            {
            size_t nRows = g_data.countRows(name);
            printf("\"%s\" is a table with:\n", name);
            printf("\t# rows: "FRMT_SIZE_T"", nRows);
            puts("");
            }
         default:;
         }
      }
   }
   
   TVoid
ReplDoPrint
   (
   Tnc8 *name
   )
   {
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         if(name)
            {
            TBaseIndex index;
            TBaseIndex index_y;
            TBaseIndex index_x;
            
            //TRACE_STR(name);
            //TRACE_INT(g_meta.countRows(name));
            printf("index ");
            for_each_row(g_meta, name, index)
               {
               //TRACE_INT(index);
               Tnc8 *s = GetString(g_meta, name, "cols", index);
               printf("%s%*s", s, (int)(20 - strlen(s)), "");
               }
             printf("\n");

             //TRACE_INT(g_data.countRows(name));
             for_each_row(g_data, name, index_y)
                {
                printf(FRMT_INT_IDX"%*s", index_y, 5 - n_digits(index_y+1), "");
                for_each_row(g_meta, name, index_x)
                   {
                   Tnc8 *col = GetString(g_meta, name, "cols", index_x);
                   if(HasInteger(g_data, name, col, index_y))
                      {
                      Ts64 integer = GetInteger(g_data, name, col, index_y);
                      printf(" %lld%*s", integer, 20 - n_digits(integer) - 1, "");
                      }
                   else if(HasString(g_data, name, col, index_y))
                      {
                      Tnc8 *s = GetString(g_data, name, col, index_y);
                      printf("\"%s\"%*s", s, (int)(20 - strlen(s) - 2), "");
                      }
                   }
                printf("\n");
                }
             }
         }
      default:;
      }
   }
   
   TVoid
ReplDoHasRow
   (
   Tnc8 *tableName,
   TBaseIndex index
   )
   {
   TBoolean result = FALSE;
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         result = g_data.hasRow(tableName, index);
      }
   if(result)
      puts(TRUE_STRING);
   else
      puts(FALSE_STRING);
   }
   
   TVoid
ReplDoHasCol
   (
   Tnc8 *tableColName
   )
   {
   TBoolean result = FALSE;
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         result = g_data.hasColumn(tableColName);
         }
      }
   if(result)
      puts(TRUE_STRING);
   else
      puts(FALSE_STRING);
   }
   
   TVoid
ReplDoHasRec 
   (
   Tnc8 *tableColName,
   TBaseIndex index
   )
   {
   TBoolean result = FALSE;
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         result = g_data.hasRecord(tableColName, index);
         }
      }
   if(result)
      puts(TRUE_STRING);
   else
      puts(FALSE_STRING);
   }
   
   TVoid
ReplDoDeleteRec 
   (
   Tnc8 *tableColName,
   TBaseIndex index
   )
   {
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         g_data.deleteRecord(tableColName, index);
         }
      }
   }
   
   TVoid 
ReplDoGetRec
   (
   Tnc8 *tableColName, 
   TBaseIndex index
   )
   {
   if(g_data.hasInteger(tableColName, index))
      {
      Ts64 integer = g_data.getInteger(tableColName, index);
      printf("%s "FRMT_INT_IDX" %lld\n", tableColName, index, integer);
      }
   else if(g_data.hasString(tableColName, index))
      {
      Tnc8 *s = g_data.getString(tableColName, index);
      printf("%s "FRMT_INT_IDX" \"%s\"\n", tableColName, index, s);
      }
   }
   
   TVoid
ReplUpdateMeta2
	(
    TBoolean add,
    Tnc8 *tableName,
    Tnc8 *colName
    )
    {
	if(add)
	   {
	   TRACE_STR(tableName);
	   TRACE_STR(colName);
       size_t iTableTables = g_meta.countRows("tables");
       size_t iTableTable = g_meta.countRows(tableName);
       g_meta.setString("tables:name", iTableTables, tableName);
       SetString(g_meta, tableName, "cols", iTableTable, colName);
	   }
    }

   TVoid
ReplUpdateMeta
    (
    TBoolean add,
    Tnc8 *tableColName
    )
    {
    //TRACE_STR(tableColName);
    Tnc8 *table = ComputeTableName(tableColName);
    //TRACE_STR(table);
    Tnc8 *col = ComputeColumnName(tableColName);
    //TRACE_STR(col);
    ReplUpdateMeta2(add, table, col);
    }
   
   
   TVoid 
ReplDoSetInt
   (
   Tnc8 *tableColName, 
   TBaseIndex index,
   Ts32 intValue
   )
   {
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         if(!g_data.hasColumn(tableColName))
            {
            ReplUpdateMeta(TRUE, tableColName);
            }
         printf("%s "FRMT_INT_IDX" %ld\n", tableColName, index, intValue);
         g_data.setInteger(tableColName, index, intValue);
         }
      }
   }

   TVoid 
ReplDoSetStr
   (
   Tnc8 *tableColName, 
   TBaseIndex index,
   Tnc8 *strValue
   )
   {
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         if(!g_data.hasColumn(tableColName))
            {
            ReplUpdateMeta(TRUE, tableColName);
            }
         printf("%s "FRMT_INT_IDX" \"%s\"\n", tableColName, index, strValue);
         g_data.setString(tableColName, index, strValue);
         }
      }
   }

   TVoid 
ReplClearIndex()
   {
   g_ia.clear();
   }

   TVoid 
ReplAddIntToIndex
   (
   Tnc8 *indexName, 
   TBaseIndex indexValue
   )
   {
   g_ia.setInteger(indexName, indexValue);
   }

   TVoid
ReplAddStrToIndex
   (
   Tnc8 *indexName,
   Tnc8 *indexValue
   )
   {
   g_ia.setString(indexName, indexValue);
   }

   TBaseIndex
ReplComputeIndex
   (
   Tnc8 *tableName
   )
   {
   //TRACE_FUN;
   //TRACE_STR(tableName);
   TBaseIndex theIndex = g_ia.findBaseIndex(g_data, tableName);
   size_t offset = 0;
   Tnc8 *indexName;
   while((indexName = g_ia.getIndexName(offset)))
      {
	  TRACE_STR(indexName);
	  Tnc8 *tableIndexName =
			  ComputeTableColumnAggregate(tableName, indexName);
	  if(g_ia.isString(offset))
		  ReplDoSetStr(
				  tableIndexName,
				  theIndex,
				  g_ia.getString(indexName)
				  );
	  else
		  ReplDoSetInt(
				  tableIndexName,
				  theIndex,
				  g_ia.getInteger(indexName)
				  );
	  offset++;
      }
   //END_LINE;
   return theIndex;
   }

   Tn8 
ReplGetNextChar()
   {
   if(g_inputIndex < strlen(g_input))
      {
      return g_input[g_inputIndex++];
      }
   else
      return EOF;
   }

   size_t
ReplGetCaretPosition()
   {
   return g_inputIndex;
   }

//#ifdef __cplusplus
//}
//#endif
