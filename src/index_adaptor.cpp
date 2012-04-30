#include <math.h>
#include <stdio.h>
#include <string.h>

#include "include/macros.h"

#include "index_adaptor.hpp"
#include "helpers.hpp"

using namespace Helpers::LazyTables;

TIndexAdaptor::TIndexAdaptor()
   {
   m_forcedBaseIndex = 0;
   }

   TVoid
TIndexAdaptor::clear()
   {
   m_indexes.clear();
   }

   TVoid
TIndexAdaptor::setInteger
   (
   Tnc8 *name,
   TIntegerIndex index
   )
   {
   if (index < LIMIT_INDEX_INT)
      {
      m_indexes[name].isInteger = TRUE;
	   m_indexes[name].iv = index;
      }
   else
	   LOG_WARNING ("Integer indexes must be between 0 and %d.", LIMIT_INDEX_INT);
   }
   
   TIntegerIndex
TIndexAdaptor::getInteger
   (
   Tnc8 *name
   )
   {
   if (m_indexes[name].isInteger)
      {
      return m_indexes[name].iv;
      }
   LOG_WARNING ("This index (\"%s\") is not an integer", name);
   return 0;
   }
   
   TVoid
TIndexAdaptor::setString
   (
   Tnc8 *name,
   Tnc8 *index
   )
   {
   m_indexes[name].isInteger = FALSE;
   if(index)
	   m_indexes[name].sv = index;
   }

   Tnc8*
TIndexAdaptor::getString
   (
   Tnc8 *name
   )
   {
   if(name)
	   if(!m_indexes[name].isInteger)
		   return m_indexes[name].sv.c_str();
   LOG_WARNING ("This index (\"%s\") is not a string", name);
   return NULL;
   }

/*!
 * Set index parameters using a format string similar to printf. Use "i" for
 * Integers and "s" for Strings. Names of the indexes are inserted before their
 * respective format specifier.
 *
 * If the @arg formatString is empty, the function accepts one additional
 * argument, a "forced" base index to use directly in the underlying indexed
 * structure.
 *
 * @param formatString
 * @return
 */
   TVoid
TIndexAdaptor::setf
   (
   Tnc8 *formatString,
   ...
   )
   {
   va_list ap;

   enum 
      {
      PARSING_START,
      PARSING_INDEX_NAME = PARSING_START,
      PARSING_GAP1,
      PARSING_INDEX_TYPE,
      PARSING_GAP2,
      PARSING_ERROR
      } parsingState = PARSING_START;

   size_t iFormatString;
   size_t iBuffer = 0;
   Tn8 indexName[32];
   if(formatString == NULL)
      {
      LOG_WARNING("Passed null format string.", formatString);
      return;
      }
   if(strlen(formatString) == 0)
      {
      Ts64 value = va_arg(ap, Ts64);
      m_forcedBaseIndex = value;
      return;
      }
   
   va_start(ap, formatString);
   for(
      iFormatString = 0; 
      iFormatString < strlen(formatString); 
      iFormatString++
      )
      {
      Tn8 c = formatString[iFormatString];
      switch(parsingState)
         {
         case PARSING_INDEX_NAME:
            {
            if(isspace(c) && iBuffer > 0)
               {
               parsingState = PARSING_GAP1;
               indexName[iBuffer] = '\0';
               iBuffer = 0;
               }
            else if(isspace(c))
               {
               LOG_WARNING("Format string must not begin with a space. ");
               parsingState = PARSING_ERROR;
               }
            else if(iBuffer < sizeof(indexName))
               indexName[iBuffer++] = c;
            break;
            }
         case PARSING_GAP1:
            {
            if(c == '%')
               parsingState = PARSING_INDEX_TYPE;
            else if(!isspace(c))
               {
               LOG_WARNING("Invalid char '%c' at position "
                  FRMT_SIZE_T" in \"%s.\" Expected '%%'. ", c, iFormatString, formatString);
               parsingState = PARSING_ERROR;
               }
            break;
         case PARSING_INDEX_TYPE:
            if(c == 'i')
               {
               Ts64 value = va_arg(ap, Ts64);
               setInteger(indexName, value);
               parsingState = PARSING_GAP2;
               }
            else if(c == 's')
               {
               Tn8* value = va_arg(ap, Tn8*);
               setString(indexName, value);
               parsingState = PARSING_GAP2;
               }
            else
               {
               parsingState = PARSING_ERROR;
               LOG_WARNING("Invalid char '%c' at position "
                  FRMT_SIZE_T" in \"%s.\" Expected either 'i' or 's'. ", c, iFormatString, formatString);
               }
            break;
            }
         case PARSING_GAP2:
            {
            if(!isspace(c))
               {
               parsingState = PARSING_INDEX_NAME;
               iFormatString--;
               continue;
               }
            }
            break;
         case PARSING_ERROR:
            {
            LOG_WARNING("Parser encountered an error.\n");
            goto done;
            }
         }
      }
   done:
   va_end(ap);
   }


   Tnc8 *
TIndexAdaptor::getIndexName
   (
   size_t offset
   )
   {
   std::map<std::string, TComplexIndex>::iterator i = m_indexes.begin();
   for(size_t j=0; j < offset && i != m_indexes.end(); j++, i++);
   if(i != m_indexes.end())
      return i->first.c_str();
   else
      return NULL;
   }

   TBoolean
TIndexAdaptor::isString
   (
   size_t offset
   )
   {
   std::map<std::string, TComplexIndex>::iterator i = m_indexes.begin();
   for(size_t j=0; j < offset && i != m_indexes.end(); j++, i++);
   if(i != m_indexes.end())
	  return !i->second.isInteger;
   else
	  return FALSE;
   }


   TBoolean 
TIndexAdaptor::isMatch
   (
   TBase &base, 
   Tnc8 *tableName, 
   TBaseIndex index
   )
   {
   std::map<std::string, TComplexIndex>::iterator i;
   for(i = m_indexes.begin(); i != m_indexes.end(); i++)
      {
      TComplexIndex &ci = i->second;
      Tnc8 *colName = i->first.c_str();
      if(HasInteger(base, tableName, colName, index))
         {
         if(ci.isInteger &&
            ci.iv != GetInteger(base, tableName, colName, index))
            {
            return FALSE;
            }
         }
      else if(HasString(base, tableName, colName, index))
         {
         if(!ci.isInteger &&
            ci.sv.compare(GetString(base, tableName, colName, index)) != 0)
            {
            return FALSE;
            }
         }
      else
         return FALSE;
      }
   return TRUE;
   }

   
   TBaseIndex
TIndexAdaptor::findBaseIndex
   (
   TBase &base, 
   Tnc8 *tableName
   )
   {
   TBaseIndex index;
   if(m_indexes.size() == 0)
      return m_forcedBaseIndex;
   
   for_each_row(base, tableName, index)
      {
      if(isMatch(base, tableName, index))
         return index;
      }
   LOG_WARNING("No matches found.\n");
   return base.end(tableName);
   }

   
   
//   std::map<std::string, TIndex>::iterator i;
//      TBaseIndex *result = new TBaseIndex;
//      //size_t position = 0;
//      for (i = m_indexes.begin(); i != m_indexes.end(); i++)
//         {
//        //TRACE_STR(i->first.c_str());
//         if (i->second.isInteger)
//            {
//           //TRACE_INT(i->second.iv);
//            //TIntegerIndex add = (TIntegerIndex)(i->second.iv * pow (LIMIT_INDEX_INT, position));
//            //if (result > LIMIT_INDEX_RAW - add)
//               //LOG_WARNING ("Overflow! "FRMT_INT_IDX" + "FRMT_INT_IDX" > "FRMT_INT_IDX, result, add, LIMIT_INDEX_RAW);
//
//            result += m_indexes[name].iv;
//            //position++;
//            }
//         else for(size_t j = 0; j < m_indexes[name].sv.length(); j++)
//             {
//             result += (TIntegerIndex)m_indexes[name].sv[j];
//             }
//         }
//      return *result;
