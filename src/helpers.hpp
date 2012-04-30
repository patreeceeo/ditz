#include "include/aditypes.h"

#define for_each_row(db, table, index) \
  for(\
     index = db.begin(table);\
     index < db.end(table);\
     index = db.next(table, index)\
     )\

namespace Helpers
  {
  namespace LazyTables
    {
    Tnc8 *ComputeTableName(Tnc8 *table_col);
    Tnc8 *ComputeColumnName(Tnc8 *table_col);
    Tnc8 *ComputeTableColumnAggregate(Tnc8 *table, Tnc8 *col);
    
    TBoolean HasColumn (TLazyTables &, Tnc8 *table, Tnc8 *col);
    TBoolean HasRecord (TLazyTables &, Tnc8 *table, Tnc8 *col, TBaseIndex index);
    TBoolean HasInteger (TLazyTables &, Tnc8 *table, Tnc8 *col, TBaseIndex index);
    TBoolean HasString (TLazyTables &, Tnc8 *table, Tnc8 *col, TBaseIndex index);
    Ts64 GetInteger (TLazyTables &, Tnc8 *table, Tnc8 *col, TBaseIndex index);
    Tnc8 *GetString (TLazyTables &, Tnc8 *table, Tnc8 *col, TBaseIndex index);
    TVoid SetInteger (TLazyTables &, Tnc8 *table, Tnc8 *col, TBaseIndex index, Ts64 integer);
    TVoid SetString (TLazyTables &, Tnc8 *table, Tnc8 *col, TBaseIndex index, Tnc8 *string);
    TVoid SetString (TLazyTables &, Tnc8 *table, Tnc8 *col, TBaseIndex index, Tnc8 *string, size_t length);
    TVoid DeleteRecord (TLazyTables &, Tnc8 *table, Tnc8 *col, TBaseIndex index);
    
    TBoolean ColumnHasString(TLazyTables &, Tnc8 *table, Tnc8 *col, Tnc8 *);
    TBoolean ColumnHasInteger(TLazyTables &, Tnc8 *table, Tnc8* col, Ts64);
    }
  }
