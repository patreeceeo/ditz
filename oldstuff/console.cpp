/*
 * console.cpp
 *
 *  Created on: Aug 30, 2011
 *      Author: patrick
 */

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

//using namespace std;
using namespace Helpers::LazyTables;

typedef enum
   {
   LAYER_LAZYTABLES
   } TLayer;

static TLazyTables g_meta;
static TLazyTables g_data;
static TLayer g_layer = LAYER_LAZYTABLES;
static T16 g_radix = 10;
static std::string tempString;

TVoid Parse(Tnc8 *);
TVoid ParseQuit();
TVoid ParseHelp();
TVoid ParseLayer();
TVoid ParseDescribe();
TVoid ParsePrint();
TVoid ParseHas();
TVoid ParseGet();
TVoid ParseSet();
TVoid ParseDelete();
Ts32 ParseString(Tnc8 **, Tnc8 *);

   int
main(int argc, char *argv[])
   {
   Tn8* input, shell_prompt[100];
   Tn8 *inputFileName;
   
   if(argc > 1)
      {
      inputFileName = argv[1];
      std::string line;
      std::ifstream myfile (inputFileName);
      if (myfile.is_open())
         {
         while ( myfile.good() )
            {
            getline (myfile, line);
            readline::add_history (line.c_str());
            Parse (line.c_str());
            }
         myfile.close ();
         }
      else
         LOG_WARNING ("Could not open \"%s.\"", inputFileName);
      }
   
   for (;;)
      {
      // getting the current user 'n path
      snprintf(shell_prompt, sizeof(shell_prompt), "%s@db > ", getenv("USER"));
      // inputing...
      input = readline::readline(shell_prompt);
      // eof
      if (!input)
         break;
      // path autocompletion when tabulation hit
      //rl_bind_key('\t', rl_complete);
      if(strlen(input) == 0)
         continue;

      // adding the previous input into history
      readline::add_history(input);
      /*do stuff*/
      Parse(input);
      }
   }

   TVoid
Parse
   (
   Tnc8 *input
   )
   {
   Tn8 *token;
   token = strtok((Tn8*)input, " ");
   while(token)
      {
      if(strcasecmp(token, "quit") == 0)
         ParseQuit();
      else if(strcasecmp(token, "help") == 0)
         ParseHelp();
      else if(strcasecmp(token, "layer") == 0)
         ParseLayer();
      else if(strcasecmp(token, "describe") == 0)
         ParseDescribe();
      else if(strcasecmp(token, "print") == 0)
         ParsePrint();
      else if(strcasecmp(token, "has") == 0)
         ParseHas();
      else if(strcasecmp(token, "get") == 0)
         ParseGet();
      else if(strcasecmp(token, "set") == 0)
         ParseSet();
      else if(strcasecmp(token, "delete") == 0)
         ParseDelete();
      else
         {
         ParseHelp();
         break;
         }
      token = strtok(NULL, " ");
      }
   }
   
   TVoid
ParseQuit()
   {
   puts("Thank you come again!");
   exit(0);
   }

   TVoid
ParseHelp()
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
               "                               - Set value of record.");
         puts("Delete <table>:<column> <index> - Delete this record.");
      }
   }

   TVoid
ParseLayer()
   {
   Tn8 *token = strtok(NULL, " ");

   if(token)
      {
      if(strcasecmp(token, "lazytables") == 0)
         g_layer = LAYER_LAZYTABLES;
      }

   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         puts("lazytables");
      default:;
      }

   }

   TVoid
ParseDescribe()
   {

   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         Tn8 *table = strtok(NULL, " ");
         if(table)
            {
            size_t nRows = g_data.countRows(table);
            printf("\"%s\" is a table with:\n", table);
            printf("\t# rows: "FRMT_SIZE_T"", nRows);
            puts("");
            }
         else
            ParseHelp();
         }
      default:;
      }
   }

   TVoid
ParsePrint()
   {
   printf("Parsing Print\n");
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         Tn8 *table = strtok(NULL, " ");
         if(table)
            {
            size_t index;
            size_t index_y;
            size_t index_x;
            
            //TRACE_STR(table);
            //TRACE_INT(g_meta.countRows(table));
            printf("index ");
            for_each_row(g_meta, table, index)            
               {
               //TRACE_INT(index);
               Tnc8 *s = GetString(g_meta, table, "cols", index);
               printf("%s%*s", s, 20 - strlen(s), "");
               }
             printf("\n");

             //TRACE_INT(g_data.countRows(table));
             for_each_row(g_data, table, index_y)
                {
                printf(FRMT_SIZE_T"%*s", index_y, 5 - n_digits(index_y), "");
                for_each_row(g_meta, table, index_x)
                   {
                   Tnc8 *col = GetString(g_meta, table, "cols", index_x);
                   if(HasInteger(g_data, table, col, index_y))
                      {
                      Ts64 integer = GetInteger(g_data, table, col, index_y);
                      printf(" %lld%*s", integer, 20 - n_digits(integer) - 1, "");
                      }
                   else if(HasString(g_data, table, col, index_y))
                      {
                      Tnc8 *s = GetString(g_data, table, col, index_y);
                      printf("\"%s\"%*s", s, 20 - strlen(s) - 2, "");
                      }
                   }
                printf("\n");
                }
            }
         else
            ParseHelp();
         }
      default:;
      }
   }


   TVoid 
ParseHas()
   {
   Tn8 *token = strtok(NULL, " ");
   TBoolean result = FALSE;
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         if(strcasecmp(token, "row") == 0)
            {
            Tn8 *table = strtok(NULL, " ");
            Tn8 *sIndex = strtok(NULL, " ");
            if(table && sIndex)
               {
               size_t index = strtol(sIndex, NULL, g_radix);
               result = g_data.hasRow(table, index);
               }
            else
               ParseHelp();
            }
         else if(strcasecmp(token, "col") == 0)
            {
            Tn8 *tableCol = strtok(NULL, " ");
            if(tableCol)
               result = g_data.hasColumn(tableCol);
            else
               ParseHelp();
            }
         else
            {
            Tn8 *tableCol = token;
            Tn8 *sIndex = strtok(NULL, " ");
            if(tableCol && sIndex)
               {
               size_t index = strtol(sIndex, NULL, g_radix);
               result = g_data.hasRecord(tableCol, index);
               }
            else
               ParseHelp();
            }
         }
      }
   if(result)
      puts(TRUE_STRING);
   else
      puts(FALSE_STRING);
   }

TVoid ParseGet()
   {
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         Tn8 *tableCol = strtok(NULL, " ");
         Tn8 *sIndex = strtok(NULL, " ");
         if(tableCol && sIndex)
            {
            size_t index = strtol(sIndex, NULL, g_radix);
            if(g_data.hasInteger(tableCol, index))
               {
               Ts64 integer = g_data.getInteger(tableCol, index);
               printf("%s "FRMT_SIZE_T" %lld\n", tableCol, index, integer);
               }
            else if(g_data.hasString(tableCol, index))
               {
               Tnc8 *s = g_data.getString(tableCol, index);
               printf("%s "FRMT_SIZE_T" \"%s\"\n", tableCol, index, s);
               }
            }
         else
            ParseHelp();
         }
      }

   }


  
  TVoid 
ParseSet()
   {
   size_t index;
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         Tnc8 *tableCol = strtok(NULL, " ");
         Tnc8 *table = ComputeTableName(tableCol);
         Tnc8 *col = ComputeColumnName(tableCol);
         Tn8 *sIndex = strtok(NULL, " ");
         Tn8 *sRawValue = strtok(NULL, " ");
         Tnc8 *sValue;
         if (tableCol && sIndex && sRawValue)
            {
            TRACE_STR(sIndex);
            if (strcmp(sIndex, "{") != 0)
               {
               index = strtol(sIndex, NULL, g_radix);
               }
            else
               {
               TIndexAdaptor ia;
               while(strcmp(sIndex, "}") != 0)
                  {
                  Tn8 *sTmp = strtok(NULL, " ");
                  Tn8 *sIndexName = (Tn8*)malloc(strlen(sTmp) + 1);
                  strcpy(sIndexName, sTmp);
                  sIndex = strtok(NULL, ", ");
                  size_t index = strtol(sIndex, NULL, g_radix);
                  ia.setInteger(sIndexName, index);
                  TRACE_STR(sIndexName);
                  TRACE_STR(sIndex);
                  free(sIndexName);
                  }
               index = ia.compute();
               }
            if (!HasColumn(g_data, table, col))
               {
               UpdateMeta(TRUE, table, col);
               }
            if (SUCCESS == ParseString(&sValue, sRawValue))
               {
               printf("%s "FRMT_SIZE_T" \"%s\"\n", tableCol, index, sValue);
               g_data.setString(tableCol, index, sValue);
               }
            else
               {
               Ts64 intValue = strtol(sRawValue, NULL, g_radix);
               printf("%s "FRMT_SIZE_T" %lld\n", tableCol, index, intValue);
               g_data.setInteger(tableCol, index, intValue);
               }
            }
         else
            ParseHelp();
         }
      }
   }

TVoid ParseDelete()
   {
   switch(g_layer)
      {
      case LAYER_LAZYTABLES:
         {
         Tn8 *tableCol = strtok(NULL, " ");
         Tn8 *sIndex = strtok(NULL, " ");
         if(tableCol && sIndex)
            {
            size_t index = strtol(sIndex, NULL, g_radix);
            g_data.deleteRecord(tableCol, index);
            }
         else
            ParseHelp();
         }
      }

   }

   Ts32
ParseString
   (
   Tnc8 **out,
   Tnc8 *in
   )
   {
   if(in && in[0] == '"' && in[strlen(in) - 1] == '"')
      {
      tempString = in;
      tempString.erase(tempString.length() - 1, 1);
      tempString.erase(0, 1);
      *out = tempString.c_str();
      return SUCCESS;
      }
   *out = in;
   return FAILURE;
   }
