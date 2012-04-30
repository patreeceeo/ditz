#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>

#include "include/types.h"
#include "include/macros.h"
#include "linear_index.hpp"

typedef std::vector<TIntegerIndex> TBase;

   TIntegerIndex
TLinearIndex::getDigit(size_t i)
   {
   if(i < this->size())
      return this->at(i);
   else
      {
      if(i > this->size())
         {
         LOG_WARNING("Position out of range:");
         TRACE_INT(i);
         END_LINE;
         }
      return 0;
      }
   }


   TVoid
TLinearIndex::setDigit(size_t i, TIntegerIndex d)
   {
   if(i >= this->size())
      this->push_back(d);
   else
      this->at(i) = d;
   }



TLinearIndex::TLinearIndex()
   {
   }

/*
 * MSE - most significant element
 */
   TLinearIndex &
TLinearIndex::operator<<(const TIntegerIndex &mse)
	{
    this->push_back(mse);
    return *this;
	}


   
   Tnc8 *
TLinearIndex::getString()
   {
   Tn8 buf[4];
   TBase esrever(this->begin(), this->end());
   std::string expanded;
   std::reverse(esrever.begin(), esrever.end());

   for(size_t i = 0; i < esrever.size(); i++)
   	   {
	   sprintf(buf, "%d", esrever.at(i));
	   expanded += buf;
	   expanded += " ";
   	   }
   return expanded.c_str();
   }
   
   
   //   TVoid
   //TBaseIndex::addAndCarry(size_t start, TIntegerIndex v)
   //   {
   //   TIntegerIndex carry = v;
   //   for(size_t i = start; carry; i++)
   //   {
   //   //Tn8 ihb = HexDigitToHalfByte(getDigit(i));
   //   TIntegerIndex id = getDigit(i);
   //   TRACE_INT(i);
   //   TRACE_INT(id);
   //   TRACE_INT(carry);
   //   END_LINE;
   //   setDigit(i, id + carry);
   //   if(LIMIT_INDEX_INT - id <= carry)
   //     carry = 1;
   //   else
   //     carry = 0;
   //   }

//   TBaseIndex &
//TBaseIndex::operator+=(const TIntegerIndex &add)
//   {
//
//   addAndCarry(0, add);
//      
//   return *this;
//   }
//   
//   TBaseIndex &
//TBaseIndex::operator=
//   (
//   const TIntegerIndex& ii
//   )
//   {
//   this->erase();
//   operator<<(ii);
//
//   return *this;
//   }