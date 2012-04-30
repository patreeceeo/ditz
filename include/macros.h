#ifndef MACROS_H_
#define MACROS_H_

#include <limits.h>

#define TRACE_FUN printf("%s: ", __FUNCTION__)
#define TRACE_STR(var) printf(#var" = \"%s\" ", var)
#define TRACE_INT(var) printf(#var" = %lld ", (Ts64)var)
#define END_LINE printf("\n")

#define LOG_WARNING(frmt, args...) printf("%s: WARNING: "frmt, __FUNCTION__, ##args)
#define LOG_INFO(frmt, args...) printf("%s: INFO: "frmt, __FUNCTION__, ##args)

#ifdef SIZE_T_MAX
#define FRMT_SIZE_T "%lu"
#define FRMTVL_SIZE_T "%*lu"
#else
#define FRMT_SIZE_T "%lu"
#define FRMTVL_SIZE_T "%*lu"
#endif

#define FRMT_INT_IDX FRMT_SIZE_T
#define FRMT_BASE_IDX FRMT_INT_IDX

#define LIMIT_INDEX_INT 256
#define LIMIT_INDEX_CHAR 95
#define LIMIT_INDEX_STR 256
#define LIMIT_HALF_BYTE 16

#ifndef SIZE_T_MAX
#define SIZE_T_MAX (-1)
#endif

#define n_digits(i) (int)ceil(log10(i+1))

#define MIN_CHAR 32
#define LIMIT_INDEX_RAW ((TIntegerIndex)(-1))

#endif
