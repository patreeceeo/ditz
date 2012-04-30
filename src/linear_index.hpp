#include <vector>
#include "include/aditypes.h"
#include "include/types.h"

class TLinearIndex : public std::vector<TIntegerIndex>
   {
   TIntegerIndex getDigit(size_t i);
   TVoid setDigit(size_t i, TIntegerIndex);
   
   public:
   TLinearIndex();

   TLinearIndex &operator<<(const TIntegerIndex &);

   Tnc8 *getString();

   //TVoid addAndCarry(size_t start, TIntegerIndex);

   //TLinearIndex &operator+=(const TIntegerIndex &);
    
   //TBaseIndex &operator=(const TBaseIndex&);
   
   //TLinearIndex &operator=(const TIntegerIndex&);
   };
