#include <cstdarg>

#include "index_adaptor.hpp"
/*
 * In future versions of this class, it would be a good idea to use 
 * TMetaTables in place of TLazyTables 
 */
#include "lazytables.hpp"


class TIndexedTables : public TLazyTables
   {
   //Tnc8 *getIndexName(Tnc8 *indexFrmtString, size_t which);
   //TBoolean getIndexIsString(Tnc8 *indexFrmtString, size_t which);
   //Ts64 getIndexInteger(Tnc8 *indexFrmtString, size_t which);
   //Tnc8 *getIndexString(Tnc8 *indexFrmtString, size_t which);
   
   public:
   TBoolean hasRecord(Tnc8 *tableName, Tnc8 *columnName, Tnc8 *indexFrmtString, ...);
   TBoolean hasInteger(Tnc8 *tableName, Tnc8 *columnName, Tnc8 *indexFrmtString, ...);
   TBoolean hasString(Tnc8 *tableName, Tnc8 *columnName, Tnc8 *indexFrmtString, ...);
   Ts64 getInteger(Tnc8 *tableName, Tnc8 *columnName, Tnc8 *indexFrmtString, ...);
   TVoid setInteger(Tnc8 *tableName, Tnc8 *columnName, Ts64 value, Tnc8 *indexFrmtString, ...);
   Tnc8 *getString(Tnc8 *tableName, Tnc8 *columnName, Tnc8 *indexFrmtString, ...);
   TVoid setString(Tnc8 *tableName, Tnc8 *columnName, Tnc8 *value, Tnc8 *indexFrmtString, ...);
   
   };