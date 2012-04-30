#include <stdio.h>
#include <cstring>
#include "../src/lazytables.hpp"
#include "../src/index_adaptor.hpp"
#include "repl.hpp"
#include "repl_embedding.hpp"
#include "include/macros.h"

main()
   {
   TLazyTables &data = ReplGetDataReference();
   TIndexAdaptor ia;
   TBaseIndex baseIndex;
   Tnc8 *sv;
   Ts64 iv;
   //ReplUseExternalBase(data);
   size_t failCount = 0, successCount = 0;

   ReplDo(
         "set person:name { dept 1, position 7 } \"Sammy\"\n"
         "set person:name { dept 2, position 6 } \"Summer\"\n"
         "set person:name { dept 3, position 5 } \"Salty\"\n"
         "set person:name { dept 4, position 4 } \"Samuri\"\n"
         "set person:name { dept 2, position 3 } \"Sasha\"\n"
         "set person:name { dept 6, position 2 } \"Summer\"\n"
         "set person:name { dept 7, position 1 } \"Seth\"\n");

   puts("Before modifying table:");
   ReplDoPrint("person");

   ia.setf("dept %i position %i", 3, 5);

   baseIndex = ia.findBaseIndex(data, "person");

   TRACE_INT(baseIndex);
   END_LINE;

   data.setString("person:name", baseIndex, "*****");

   puts("After test 1:");
   ReplDoPrint("person");

   sv = data.getString("person:name", 2);
   if(strcmp(sv, "*****") != 0)
      {
      puts("FAILURE 1");
      failCount++;
      }
   else
      successCount++;

   ia.clear();

   ia.setf("position %i name %s", 6, "Summer");

   baseIndex = ia.findBaseIndex(data, "person");
   data.setInteger("person:dept", baseIndex, 22);

   puts("After test 2:");
   ReplDoPrint("person");

   iv = data.getInteger("person:dept", 1);
   if(iv != 22)
      {
      failCount++;
      puts("FAILURE 2");
      }
   else
      successCount++;

   printf(""FRMT_SIZE_T" success. "FRMT_SIZE_T" failures\n", successCount, failCount);
   }
