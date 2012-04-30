/*****************************************************************************/
/*!
  @file
  Filename:             TYPES.H
  Main Programmer:      AGA
  Assistance by:
  Creation Date:        Dec 16, 1997
  Last Edit:            $Date: 2010/09/11 18:21:33 $ by $Author: davido $
  Description:          Header File containing all universal system types
  Special Notes:        This is used to allow T? types for all standard types
*****************************************************************************/

#ifndef  ADITYPES_H                        /* Include only once */
#define  ADITYPES_H                        /* Define it */

/* should this really be here? */
//using namespace std;

#define  __pack__    __attribute__((packed)) //pack structures attribute

/* User Specified Typedefs -------------------------------------------------*/
typedef void                                  TVoid;
typedef volatile void                         TvVoid;

typedef unsigned char                         T8;
typedef const unsigned char                   Tc8;
typedef volatile unsigned char                Tv8;
typedef volatile const unsigned char          Tvc8;
typedef unsigned short int                    T16;
typedef const unsigned short int              Tc16;
typedef volatile unsigned short int           Tv16;
typedef volatile const unsigned short int     Tvc16;
typedef unsigned long int                     T32;
typedef const unsigned long int               Tc32;
typedef volatile unsigned long int            Tv32;
typedef volatile const unsigned long int      Tvc32;
typedef unsigned long long int                T64;
typedef const unsigned long long int          Tc64;
typedef volatile unsigned long long int       Tv64;
typedef volatile const unsigned long long int Tvc64;
typedef float                                 TFloat;
typedef const float                           TcFloat;
typedef volatile float                        TvFloat;

typedef signed char                           Ts8;
typedef const signed char                     Tsc8;
typedef volatile signed char                  Tsv8;
typedef volatile const signed char            Tsvc8;
typedef signed short int                      Ts16;
typedef const signed short int                Tsc16;
typedef volatile signed short int             Tsv16;
typedef volatile const signed short int       Tsvc16;
typedef signed long int                       Ts32;
typedef const signed long int                 Tsc32;
typedef volatile signed long int              Tsv32;
typedef volatile const signed long int        Tsvc32;
typedef signed long long int                  Ts64;
typedef const signed long long int            Tsc64;
typedef volatile signed long long int         Tsv64;
typedef volatile const signed long long int   Tsvc64;

#ifdef __cplusplus
typedef bool                                  TBoolean;
typedef const bool                            TcBoolean;
typedef volatile bool                         TvBoolean;
#else // __cplusplus not defined
typedef long                                  TBoolean;
typedef const long                            TcBoolean;
typedef volatile long                         TvBoolean;
#endif // __cplusplus

typedef struct timeval  TTv;
typedef const TTv       TcTv;


/* DWG 2005-05-09:
 * 
 * NOTE- In C/C++, the char types are treated specially, with 'char', 
 * 'signed char', and 'unsigned char' each treated as a different type.
 * Also, a plain 'char' may or may not be signed, and is compiler specific.
 * 
 * Thus an additional set of typedefs are useful.  The 'n' identifier is
 * used in the signed position (as in 'none', 'neither', 'n/a', etc)
 */
typedef char                                  Tn8;
typedef const char                            Tnc8;
typedef volatile char                         Tnv8;
typedef volatile const char                   Tnvc8;

/* User Defined General Purpose Macros -------------------------------------*/
/* Safe Denominator Macro, guarantees a safe dividend, A if nonzero, B if nonzero, else 1 */
#define SafeDenominator(A,B)   ((A) ? (A) : ((B) ? (B) : 1))

/* General Purpose Constants -----------------------------------------------*/
#define CPUCLK05_NSEC   5               /* CPU Clock is 5 nSec */

#define NIL             0               /* Nothing (or Zero) */
#define NYBBLE_MASK     0x0F            /* Nybble Mask */
#define LO_NYBBLE       0x0F            /* Lo Nybble Mask */
#define HI_NYBBLE       0xF0            /* Hi Nybble Mask */
#define BYTE_MASK       0xFF            /* Byte Mask */
#define LO_BYTE_MASK    0x00FF          /* Lo Byte Mask for Word */
#define HI_BYTE_MASK    0xFF00          /* Hi Byte Mask for Word */
#define WORD_MASK       0xFFFF          /* Word Mask */
#define LO_SIX_NIBBLE_MASK   0x00FFFFFF    /*  low Six nibble mask*/
#define LO_WORD_MASK    0x0000FFFF      /* Lo Word Mask for Long */
#define HI_WORD_MASK    0xFFFF0000      /* Hi Word Mask for Long */
#define LONG_MASK       0xFFFFFFFF      /* Long Mask */
#define BIT_7           0x80            /* Most significant bit in a byte */
#define BIT_15          0x8000          /* Most significant bit in a word */
#define BIT_31          0x80000000      /* Most significant bit in a long */
#define BITS_PER_NYBBLE 4               /* 4 bits per byte */
#define BITS_PER_BYTE   8               /* 8 bits per byte */
#define BITS_PER_WORD   16              /* 16 bits per word */
#define BITS_PER_LONG   32              /* 32 bits per long */

#define BYTES_PER_WORD  2               /* 2 bytes per word */
#define BYTES_PER_LONG  4               /* 4 bytes per long */
#define WORDS_PER_LONG  2               /* 2 words per long */
#define WORD_ALIGNMENT_MASK (~(sizeof(T16)-1))  /* Word alignment mask */
#define LONG_ALIGNMENT_MASK (~(sizeof(T32)-1))  /* Long alignment mask */

#ifdef __cplusplus
#define FALSE           false           /* Boolean False */
#define TRUE            true            /* Boolean True */
#else // __cplusplus not defined
#define FALSE           0               /* Boolean False */
#define TRUE            (!FALSE)        /* Boolean True */
#endif
#define OFF             0
#define ON              (!OFF)
#define SUCCESS         0
#define FAILURE         (!SUCCESS)
#define LO              0
#define HI              1
#define NO              0
#define YES             (!NO)
enum
   {
   NO_STR = 0,   
   YES_STR
   };

#define BKSP            0x08            /* Backspace character */
#define LF              0x0A            /* Line Feed (LF) character */
#define CR              0x0D            /* Carriage Return (CR) character */
#define SPACE           0x20            /* Space (SP) character */
#define DOT             0x2E            /* Dot (.) character */
#define EMPTY_PLACEHOLDER 0x7E          /* Empty place holder (~) character */
#define FILE_ERASED     0xE5            /* First character of an erased file */
#define CARAT           0x5E            /* Carat (^) character */

#define ONE             1               /* Decimal 1 */
#define TEN             10              /* Decimal 10 */
#define HUNDRED         100             /* Decimal 100 */
#define THOUSAND        1000            /* Decimal 1000 */
#define TENTHOUSAND     10000           /* Decimal 10000 */
#define HUNDREDTHOUSAND 100000          /* Decimal 100000 */
#define MILLION         1000000         /* Decimal 1000000 */
#define TENMILLION      10000000        /* Decimal 10000000 */
#define HUNDREDMILLION  100000000       /* Decimal 100000000 */
#define BILLION         1000000000      /* Decimal 1000000000 */

#define MB              1048576         /* 1 MB */
#define MByte           1000000         /* 1 Million Bytes */
#define KB              1024            /* 1 KB */
#define KByte           1000            /* 1 Thousand Bytes */

#define FR_PER_SE_NTSC  30              /* Frames per Second, NTSC */
#define FR_PER_SE_PAL   25              /* Frames per Second, PAL */
#define SE_PER_MN       60              /* Seconds per Minute */
#define SE_PER_HR       3600            /* Seconds per Hour */
#define SE_PER_DY       86400           /* Seconds per Day */
#define MN_PER_HR       60              /* Minutes per Hour */
#define MN_PER_DY       1440            /* Minutes per Day */
#define HR_PER_DY       24              /* Hours per Day */
#define MO_PER_YR       12              /* Months per year */
#define STC_PER_MS      (9*TEN)         /* STC per millisecond */
#define STC_PER_SE      (9*TENTHOUSAND) /* STC per Second */
#define STC_PER_FR_NTSC 3003
#define STC_PER_FR_PAL  3600
#define US_PER_SE       MILLION
#define US_PER_MS       THOUSAND
#define MS_PER_SE       THOUSAND

/* These defines allow declaration of character arrays (C strings) that will
 * hold ASCII converted strings.  Note that signed values may include the sign
 * (+/-) character. 
 */
#define T8_MAX_STR_SIZE       4  //!< 255, 3 chars plus NULL
#define T16_MAX_STR_SIZE      6  //!< 65535, 5 chars plus NULL
#define T32_MAX_STR_SIZE      11 //!< 4.29x10^9, 10 chars plus NULL
#define T64_MAX_STR_SIZE      21 //!< 18.45x10^18, 20 chars plus NULL
#define Ts8_MAX_STR_SIZE      5  //!< +127/-128, 4 chars plus NULL
#define Ts16_MAX_STR_SIZE     7  //!< +32767/-32768, 6 chars plus NULL
#define Ts32_MAX_STR_SIZE     12 //!< +/-2.15x10^9, 11 chars plus NULL
#define Ts64_MAX_STR_SIZE     21 //!< +/-9.22x10^18, 20 chars plus NULL

//! Moved from ./app/include/dpi1200 
typedef enum ADStatus
   {
   ADSTAT_SUCCESS = 0,   //!<Must be zero
   ADSTAT_EFAIL,
   ADSTAT_ESIG_HNDLR,
   ADSTAT_EACCES,
   ADSTAT_EINVAL,
   ADSTAT_EINIT,
   ADSTAT_ENODATA,
   ADSTAT_EDISCONNECT,
   ADSTAT_EINPROGRESS,
   ADSTAT_ESAMEVAL,           // Indicates same value (thus no save)
   ADSTAT_EAVAIL,
   ADSTAT_ERROR_OPENINGFILE,
   ADSTAT_ERROR_LOCKINGFILE,
   ADSTAT_ENOCHILD,
   ADSTAT_EGETSYSTIME,    //Error getting system time

   //! Error status for scheduler
   ADSTAT_EALLWINDOWS_CLOSED  = 1000,
   ADSTAT_ENOWINDOWS,
   ADSTAT_EALLAVAILS_PLAYED,
   ADSTAT_ENO_WINDOW_TOTRIGGER,
   ADSTAT_EALLBREAKS_AVAILABLE
   } TADStatus;

/*==========================================================================*/
#endif
