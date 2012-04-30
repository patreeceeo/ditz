
#ifndef REPL_HPP_
#define REPL_HPP_


#include "include/aditypes.h"
#include "include/types.h"

#include "parser.h"

#ifdef __cplusplus
extern "C" {
#endif

TVoid Initialize_repl ();

TVoid ReplDoHelp ();

TVoid ReplSetInput (Tnc8 *input, TBoolean dynamic);

TBoolean ReplItsQuittingTime ();

TVoid ReplBeginQuit ();

TVoid ReplDoQuit ();

TVoid ReplDoPrompt ();

TVoid ReplSetLayer (Tn8 *layerName);

TVoid ReplDoDescribe (Tnc8 *name);

TVoid ReplDoPrint (Tnc8 *name);

TVoid ReplDoHasRow (Tnc8 *tableName, TBaseIndex index);

TVoid ReplDoHasCol (Tnc8 *tableColName);

TVoid ReplDoHasRec (Tnc8 *tableColName, TBaseIndex index);

TVoid ReplDoDeleteRec (Tnc8 *tableColName, TBaseIndex index);

TVoid ReplDoGetRec (Tnc8 *tableColName, TBaseIndex index);

TVoid ReplDoSetInt (Tnc8 *tableColName, TBaseIndex index, Ts32 intValue);

TVoid ReplDoSetStr (Tnc8 *tableColName, TBaseIndex index, Tnc8 *strValue);

TVoid ReplClearIndex ();

TVoid ReplAddIntToIndex (Tnc8 *indexName, TBaseIndex indexCol);

TVoid ReplAddStrToIndex (Tnc8 *indexName, Tnc8 *indexCol);

TBaseIndex ReplComputeIndex (Tnc8 *tableName);

Tn8 ReplGetNextChar ();

size_t ReplGetCaretPosition();
#ifdef __cplusplus
}
#endif


#endif // REPL_HPP_

