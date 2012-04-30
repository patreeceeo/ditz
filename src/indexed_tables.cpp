#include "indexed_tables.hpp"

   TBoolean 
TIndexedTables::hasRecord
   (
   Tnc8 *tableName, 
   Tnc8 *columnName, 
   Tnc8 *indexFrmtString, 
   ...
   )
   {
   va_list ap;
   size_t iFrmtString;
   Tnc8 *indexName;
   Ts64 intIndex = 0;
   Tnc8 *strIndex = "";
   va_start(ap, count); //Requires the last fixed parameter (to get the address)
   for(j=0; j<count; j++)
      tot+=va_arg(ap, double); //Requires the type to cast to. Increments ap to the next argument.
   va_end(ap);
   return tot/count;
   }