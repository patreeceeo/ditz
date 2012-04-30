#include "include/aditypes.h"

extern Tn8 lineBuf[256];
extern TBoolean g_parsingFinished;
extern TBoolean g_parsingError;
extern TBoolean g_useIntValue;

#ifdef __cplusplus
extern "C" {
#endif
TVoid ReplDo (Tnc8 *pUtterance);
#ifdef __cplusplus
}
#endif