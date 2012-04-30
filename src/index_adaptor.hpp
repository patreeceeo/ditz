#include <map>
#include <string>
#include <cstdarg>

#include "include/aditypes.h"
#include "include/types.h"

#include "lazytables.hpp"

class TIndexAdaptor
   {
   typedef TLazyTables TBase;
   
   typedef struct
      {
	   TBoolean isInteger;
	   TIntegerIndex iv;
       std::string sv;
	   } TComplexIndex;
	   
   std::map<std::string, TComplexIndex> m_indexes;
   TBaseIndex m_forcedBaseIndex;
   
   TBoolean isMatch(TBase &base, Tnc8 *tableName, TBaseIndex index);
   
   public:
      TIndexAdaptor();
      TVoid clear();
      TVoid setInteger(Tnc8 *name, TIntegerIndex index);
      TIntegerIndex getInteger(Tnc8 *name);
      TVoid setString(Tnc8 *name, Tnc8 *index);
      Tnc8 *getString(Tnc8 *name);
      TVoid setf(Tnc8 *, ...);
      TVoid getf(Tnc8 *, ...);
      Tnc8 *getIndexName(size_t offset);
      TBoolean isString(size_t offset);
      TBaseIndex findBaseIndex(TBase &base, Tnc8 *tableName);
   };
