#include <stdio.h>

#include "../include/macros.h"
#include "../src/base_index.hpp"

/*
 * This is a TEST program for TBaseIndex, not the class definition.
 */

main()
   {
   TBaseIndex bi1, bi2, bi3, bi4, bi5, bi6;
   
//   puts("bi1");
//   (bi1 += 2)
//      += 2;
//
//   puts("bi2");
//   (bi2 += 400)
//      += 600;

   puts("bi3");
   bi3 << 1 << 2 << 3;
   
//   puts("bi4");
//   (bi4 += 'D')
//      += 'A';
//
//   puts("bi5");
//   (bi5 += 'r')
//      += '0';
//
//   puts("bi6");
//   bi6 = 0xFEDCBA;

//   TRACE_STR(bi1.getString());
//   END_LINE;
//   TRACE_STR(bi2.getString());
//   END_LINE;
   TRACE_STR(bi3.getString());
   END_LINE;
//   TRACE_STR(bi4.getString());
//   END_LINE;
//   TRACE_STR(bi5.getString());
//   END_LINE;
//   TRACE_STR(bi6.getString());
//   END_LINE;
   }
