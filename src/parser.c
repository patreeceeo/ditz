/* A recursive-descent parser generated by peg 0.1.2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYRULECOUNT 22


  #include "repl.hpp"

  #define YYSTYPE Tn8 *
  
  #define DUP \
    yy = strdup(yytext)
  
  #define CPY strcpy
  
  #define P printf
  
//  #define DEFER(S, ...) \
//    sprintf(buf, S "\n", __VA_ARGS__); strcat(defer, buf);
  
  #define YY_INPUT(buf, result, max_size) { \
      int yyc = ReplGetNextChar(); \
      /*if(yyc == EOF)\
	puts("next char = EOF");\
      else\
      	printf("next char = %c\n", yyc);*/\
      result = (EOF == yyc) ? 0 : (*(buf)= yyc, 1); \
      yyprintf((stderr, "<%c>", yyc)); \
      }
      
  Tn8 n[80];
  Tn8 ln[80];
  Tn8 tn[80];
  Tn8 tcn[80];
  Tn8 s[80];

  Ts32 i;
  TBaseIndex theIndex;
  Tn8 lineBuf[256];
  TBoolean g_parsingFinished = FALSE;
  TBoolean g_parsingError = FALSE;
  TBoolean g_useIntValue = TRUE;


#ifndef YY_VARIABLE
#define YY_VARIABLE(T)	static T
#endif
#ifndef YY_LOCAL
#define YY_LOCAL(T)	static T
#endif
#ifndef YY_ACTION
#define YY_ACTION(T)	static T
#endif
#ifndef YY_RULE
#define YY_RULE(T)	static T
#endif
#ifndef YY_PARSE
#define YY_PARSE(T)	T
#endif
#ifndef YYPARSE
#define YYPARSE		yyparse
#endif
#ifndef YYPARSEFROM
#define YYPARSEFROM	yyparsefrom
#endif
#ifndef YY_INPUT
#define YY_INPUT(buf, result, max_size)			\
  {							\
    int yyc= getchar();					\
    result= (EOF == yyc) ? 0 : (*(buf)= yyc, 1);	\
    yyprintf((stderr, "<%c>", yyc));			\
  }
#endif
#ifndef YY_BEGIN
#define YY_BEGIN	( yybegin= yypos, 1)
#endif
#ifndef YY_END
#define YY_END		( yyend= yypos, 1)
#endif
#ifdef YY_DEBUG
# define yyprintf(args)	fprintf args
#else
# define yyprintf(args)
#endif
#ifndef YYSTYPE
#define YYSTYPE	int
#endif

#ifndef YY_PART

typedef void (*yyaction)(char *yytext, int yyleng);
typedef struct _yythunk { int begin, end;  yyaction  action;  struct _yythunk *next; } yythunk;

YY_VARIABLE(char *   ) yybuf= 0;
YY_VARIABLE(int	     ) yybuflen= 0;
YY_VARIABLE(int	     ) yypos= 0;
YY_VARIABLE(int	     ) yylimit= 0;
YY_VARIABLE(char *   ) yytext= 0;
YY_VARIABLE(int	     ) yytextlen= 0;
YY_VARIABLE(int	     ) yybegin= 0;
YY_VARIABLE(int	     ) yyend= 0;
YY_VARIABLE(int	     ) yytextmax= 0;
YY_VARIABLE(yythunk *) yythunks= 0;
YY_VARIABLE(int	     ) yythunkslen= 0;
YY_VARIABLE(int      ) yythunkpos= 0;
YY_VARIABLE(YYSTYPE  ) yy;
YY_VARIABLE(YYSTYPE *) yyval= 0;
YY_VARIABLE(YYSTYPE *) yyvals= 0;
YY_VARIABLE(int      ) yyvalslen= 0;

YY_LOCAL(int) yyrefill(void)
{
  int yyn;
  while (yybuflen - yypos < 512)
    {
      yybuflen *= 2;
      yybuf= realloc(yybuf, yybuflen);
    }
  YY_INPUT((yybuf + yypos), yyn, (yybuflen - yypos));
  if (!yyn) return 0;
  yylimit += yyn;
  return 1;
}

YY_LOCAL(int) yymatchDot(void)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  ++yypos;
  return 1;
}

YY_LOCAL(int) yymatchChar(int c)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  if (yybuf[yypos] == c)
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchChar(%c) @ %s\n", c, yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchChar(%c) @ %s\n", c, yybuf+yypos));
  return 0;
}

YY_LOCAL(int) yymatchString(char *s)
{
  int yysav= yypos;
  while (*s)
    {
      if (yypos >= yylimit && !yyrefill()) return 0;
      if (yybuf[yypos] != *s)
        {
          yypos= yysav;
          return 0;
        }
      ++s;
      ++yypos;
    }
  return 1;
}

YY_LOCAL(int) yymatchClass(unsigned char *bits)
{
  int c;
  if (yypos >= yylimit && !yyrefill()) return 0;
  c= yybuf[yypos];
  if (bits[c >> 3] & (1 << (c & 7)))
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchClass @ %s\n", yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchClass @ %s\n", yybuf+yypos));
  return 0;
}

YY_LOCAL(void) yyDo(yyaction action, int begin, int end)
{
  while (yythunkpos >= yythunkslen)
    {
      yythunkslen *= 2;
      yythunks= realloc(yythunks, sizeof(yythunk) * yythunkslen);
    }
  yythunks[yythunkpos].begin=  begin;
  yythunks[yythunkpos].end=    end;
  yythunks[yythunkpos].action= action;
  ++yythunkpos;
}

YY_LOCAL(int) yyText(int begin, int end)
{
  int yyleng= end - begin;
  if (yyleng <= 0)
    yyleng= 0;
  else
    {
      while (yytextlen < (yyleng - 1))
	{
	  yytextlen *= 2;
	  yytext= realloc(yytext, yytextlen);
	}
      memcpy(yytext, yybuf + begin, yyleng);
    }
  yytext[yyleng]= '\0';
  return yyleng;
}

YY_LOCAL(void) yyDone(void)
{
  int pos;
  for (pos= 0;  pos < yythunkpos;  ++pos)
    {
      yythunk *thunk= &yythunks[pos];
      int yyleng= thunk->end ? yyText(thunk->begin, thunk->end) : thunk->begin;
      yyprintf((stderr, "DO [%d] %p %s\n", pos, thunk->action, yytext));
      thunk->action(yytext, yyleng);
    }
  yythunkpos= 0;
}

YY_LOCAL(void) yyCommit()
{
  if ((yylimit -= yypos))
    {
      memmove(yybuf, yybuf + yypos, yylimit);
    }
  yybegin -= yypos;
  yyend -= yypos;
  yypos= yythunkpos= 0;
}

YY_LOCAL(int) yyAccept(int tp0)
{
  if (tp0)
    {
      fprintf(stderr, "accept denied at %d\n", tp0);
      return 0;
    }
  else
    {
      yyDone();
      yyCommit();
    }
  return 1;
}

YY_LOCAL(void) yyPush(char *text, int count)	{ yyval += count; }
YY_LOCAL(void) yyPop(char *text, int count)	{ yyval -= count; }
YY_LOCAL(void) yySet(char *text, int count)	{ yyval[count]= yy; }

#endif /* YY_PART */

#define	YYACCEPT	yyAccept(yythunkpos0)

YY_RULE(int) yy_EOF(); /* 22 */
YY_RULE(int) yy_nl(); /* 21 */
YY_RULE(int) yy_ws(); /* 20 */
YY_RULE(int) yy_complex_index(); /* 19 */
YY_RULE(int) yy_index(); /* 18 */
YY_RULE(int) yy__(); /* 17 */
YY_RULE(int) yy_value(); /* 16 */
YY_RULE(int) yy_string(); /* 15 */
YY_RULE(int) yy_var_stmt(); /* 14 */
YY_RULE(int) yy_str_value(); /* 13 */
YY_RULE(int) yy_int_value(); /* 12 */
YY_RULE(int) yy_rec_spec(); /* 11 */
YY_RULE(int) yy_col_spec(); /* 10 */
YY_RULE(int) yy_row_spec(); /* 9 */
YY_RULE(int) yy_name(); /* 8 */
YY_RULE(int) yy_layer_name(); /* 7 */
YY_RULE(int) yy_s(); /* 6 */
YY_RULE(int) yy_stmt(); /* 5 */
YY_RULE(int) yy_meta_stmt(); /* 4 */
YY_RULE(int) yy_EOL(); /* 3 */
YY_RULE(int) yy_ui_stmt(); /* 2 */
YY_RULE(int) yy_top_stmt(); /* 1 */

YY_ACTION(void) yy_2_complex_index(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_2_complex_index\n"));
   if(g_useIntValue) ReplAddIntToIndex (n, i); else ReplAddStrToIndex(n, s); ;
#undef n
}
YY_ACTION(void) yy_1_complex_index(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_1_complex_index\n"));
   if(g_useIntValue) ReplAddIntToIndex (n, i); else ReplAddStrToIndex(n, s); ;
#undef n
}
YY_ACTION(void) yy_2_index(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_index\n"));
   theIndex = ReplComputeIndex (tn); ReplClearIndex(); ;
}
YY_ACTION(void) yy_1_index(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_index\n"));
   theIndex = strtol (yytext, NULL, 10); ;
}
YY_ACTION(void) yy_1_col_spec(char *yytext, int yyleng)
{
#define n2 yyval[-1]
#define n1 yyval[-2]
  yyprintf((stderr, "do yy_1_col_spec\n"));
   CPY (tcn, n1); strcat(tcn, ":"); strcat (tcn, n2); CPY (tn, n1); ;
#undef n2
#undef n1
}
YY_ACTION(void) yy_1_row_spec(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_1_row_spec\n"));
   CPY (tn, n); ;
#undef n
}
YY_ACTION(void) yy_1_name(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_name\n"));
   DUP; ;
}
YY_ACTION(void) yy_3_var_stmt(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_3_var_stmt\n"));
   ReplDoGetRec (tcn, theIndex); ;
}
YY_ACTION(void) yy_2_var_stmt(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_var_stmt\n"));
   ReplDoSetStr (tcn, theIndex, s); ;
}
YY_ACTION(void) yy_1_var_stmt(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_var_stmt\n"));
   ReplDoSetInt (tcn, theIndex, i); ;
}
YY_ACTION(void) yy_1_string(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_string\n"));
   CPY (s, yytext); ;
}
YY_ACTION(void) yy_2_value(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_value\n"));
   g_useIntValue = FALSE; ;
}
YY_ACTION(void) yy_1_value(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_value\n"));
   g_useIntValue = TRUE; ;
}
YY_ACTION(void) yy_1_int_value(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_int_value\n"));
   i = strtol (yytext, NULL, 10); ;
}
YY_ACTION(void) yy_8_stmt(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_8_stmt\n"));
   ReplDoDeleteRec (tcn, theIndex); ;
#undef n
}
YY_ACTION(void) yy_7_stmt(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_7_stmt\n"));
   ReplDoSetStr (tcn, theIndex, s); ;
#undef n
}
YY_ACTION(void) yy_6_stmt(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_6_stmt\n"));
   ReplDoSetInt (tcn, theIndex, i); ;
#undef n
}
YY_ACTION(void) yy_5_stmt(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_5_stmt\n"));
   ReplDoGetRec (tcn, theIndex); ;
#undef n
}
YY_ACTION(void) yy_4_stmt(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_4_stmt\n"));
   ReplDoHasRec (tcn, theIndex); ;
#undef n
}
YY_ACTION(void) yy_3_stmt(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_3_stmt\n"));
   ReplDoHasCol (tcn); ;
#undef n
}
YY_ACTION(void) yy_2_stmt(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_2_stmt\n"));
   ReplDoHasRow (tn, theIndex); ;
#undef n
}
YY_ACTION(void) yy_1_stmt(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_1_stmt\n"));
   ReplDoPrint (n); ;
#undef n
}
YY_ACTION(void) yy_1_meta_stmt(char *yytext, int yyleng)
{
#define n yyval[-1]
  yyprintf((stderr, "do yy_1_meta_stmt\n"));
   ReplDoDescribe (n); ;
#undef n
}
YY_ACTION(void) yy_3_ui_stmt(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_3_ui_stmt\n"));
   ReplBeginQuit (); ;
}
YY_ACTION(void) yy_2_ui_stmt(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_ui_stmt\n"));
   //ReplSetLayer (ln); ;
}
YY_ACTION(void) yy_1_ui_stmt(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_ui_stmt\n"));
   ReplDoHelp (); ;
}
YY_ACTION(void) yy_2_top_stmt(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_top_stmt\n"));
   g_parsingError = TRUE; ;
}
YY_ACTION(void) yy_1_top_stmt(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_top_stmt\n"));
   g_parsingFinished = TRUE; P("finished stmt\n"); ;
}

YY_RULE(int) yy_EOF()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "EOF"));
  {  int yypos2= yypos, yythunkpos2= yythunkpos;  if (!yymatchDot()) goto l2;  goto l1;
  l2:;	  yypos= yypos2; yythunkpos= yythunkpos2;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "EOF", yybuf+yypos));
  return 1;
  l1:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "EOF", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_nl()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "nl"));
  {  int yypos4= yypos, yythunkpos4= yythunkpos;  if (!yymatchString("\r\n")) goto l5;  goto l4;
  l5:;	  yypos= yypos4; yythunkpos= yythunkpos4;  if (!yymatchChar('\r')) goto l6;  goto l4;
  l6:;	  yypos= yypos4; yythunkpos= yythunkpos4;  if (!yymatchChar('\n')) goto l3;
  }
  l4:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "nl", yybuf+yypos));
  return 1;
  l3:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "nl", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_ws()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "ws"));
  {  int yypos8= yypos, yythunkpos8= yythunkpos;  if (!yymatchChar(' ')) goto l9;  goto l8;
  l9:;	  yypos= yypos8; yythunkpos= yythunkpos8;  if (!yymatchChar('\t')) goto l10;  goto l8;
  l10:;	  yypos= yypos8; yythunkpos= yythunkpos8;  if (!yy_nl()) goto l7;
  }
  l8:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "ws", yybuf+yypos));
  return 1;
  l7:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "ws", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_complex_index()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "complex_index"));  if (!yy_name()) goto l11;  yyDo(yySet, -1, 0);  if (!yy_s()) goto l11;  if (!yy_value()) goto l11;  yyDo(yy_1_complex_index, yybegin, yyend);
  l12:;	
  {  int yypos13= yypos, yythunkpos13= yythunkpos;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l13;  if (!yymatchChar(',')) goto l13;  yyText(yybegin, yyend);  if (!(YY_END)) goto l13;  if (!yy__()) goto l13;  if (!yy_name()) goto l13;  yyDo(yySet, -1, 0);  if (!yy_s()) goto l13;  if (!yy_value()) goto l13;  yyDo(yy_2_complex_index, yybegin, yyend);  goto l12;
  l13:;	  yypos= yypos13; yythunkpos= yythunkpos13;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "complex_index", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l11:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "complex_index", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_index()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "index"));
  {  int yypos15= yypos, yythunkpos15= yythunkpos;  if (!yy_int_value()) goto l16;  yyDo(yy_1_index, yybegin, yyend);  goto l15;
  l16:;	  yypos= yypos15; yythunkpos= yythunkpos15;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l14;  if (!yymatchChar('{')) goto l14;  yyText(yybegin, yyend);  if (!(YY_END)) goto l14;  if (!yy__()) goto l14;  if (!yy_complex_index()) goto l14;  if (!yy__()) goto l14;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l14;  if (!yymatchChar('}')) goto l14;  yyText(yybegin, yyend);  if (!(YY_END)) goto l14;  yyDo(yy_2_index, yybegin, yyend);
  }
  l15:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "index", yybuf+yypos));
  return 1;
  l14:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "index", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy__()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "_"));
  {  int yypos18= yypos, yythunkpos18= yythunkpos;
  l20:;	
  {  int yypos21= yypos, yythunkpos21= yythunkpos;  if (!yy_ws()) goto l21;  goto l20;
  l21:;	  yypos= yypos21; yythunkpos= yythunkpos21;
  }  goto l18;
  l19:;	  yypos= yypos18; yythunkpos= yythunkpos18;
  {  int yypos22= yypos, yythunkpos22= yythunkpos;  if (!yy_EOF()) goto l22;  goto l23;
  l22:;	  yypos= yypos22; yythunkpos= yythunkpos22;
  }
  l23:;	
  }
  l18:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "_", yybuf+yypos));
  return 1;
  l17:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "_", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_value()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "value"));
  {  int yypos25= yypos, yythunkpos25= yythunkpos;  if (!yy_int_value()) goto l26;  yyDo(yy_1_value, yybegin, yyend);  goto l25;
  l26:;	  yypos= yypos25; yythunkpos= yythunkpos25;  if (!yy_str_value()) goto l24;  yyDo(yy_2_value, yybegin, yyend);
  }
  l25:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "value", yybuf+yypos));
  return 1;
  l24:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "value", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_string()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "string"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l27;
  l28:;	
  {  int yypos29= yypos, yythunkpos29= yythunkpos;
  {  int yypos30= yypos, yythunkpos30= yythunkpos;  if (!yymatchChar('"')) goto l30;  goto l29;
  l30:;	  yypos= yypos30; yythunkpos= yythunkpos30;
  }  if (!yymatchDot()) goto l29;  goto l28;
  l29:;	  yypos= yypos29; yythunkpos= yythunkpos29;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l27;  yyDo(yy_1_string, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "string", yybuf+yypos));
  return 1;
  l27:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "string", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_var_stmt()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "var_stmt"));
  {  int yypos32= yypos, yythunkpos32= yythunkpos;  if (!yy_rec_spec()) goto l33;  if (!yy__()) goto l33;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l33;  if (!yymatchChar('=')) goto l33;  yyText(yybegin, yyend);  if (!(YY_END)) goto l33;  if (!yy__()) goto l33;  if (!yy_int_value()) goto l33;  yyDo(yy_1_var_stmt, yybegin, yyend);  goto l32;
  l33:;	  yypos= yypos32; yythunkpos= yythunkpos32;  if (!yy_rec_spec()) goto l34;  if (!yy__()) goto l34;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l34;  if (!yymatchChar('=')) goto l34;  yyText(yybegin, yyend);  if (!(YY_END)) goto l34;  if (!yy__()) goto l34;  if (!yy_str_value()) goto l34;  yyDo(yy_2_var_stmt, yybegin, yyend);  goto l32;
  l34:;	  yypos= yypos32; yythunkpos= yythunkpos32;  if (!yy_rec_spec()) goto l31;  yyDo(yy_3_var_stmt, yybegin, yyend);
  }
  l32:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "var_stmt", yybuf+yypos));
  return 1;
  l31:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "var_stmt", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_str_value()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "str_value"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l35;  if (!yymatchChar('"')) goto l35;  yyText(yybegin, yyend);  if (!(YY_END)) goto l35;  if (!yy_string()) goto l35;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l35;  if (!yymatchChar('"')) goto l35;  yyText(yybegin, yyend);  if (!(YY_END)) goto l35;
  yyprintf((stderr, "  ok   %s @ %s\n", "str_value", yybuf+yypos));
  return 1;
  l35:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "str_value", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_int_value()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "int_value"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l36;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\003\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l36;
  l37:;	
  {  int yypos38= yypos, yythunkpos38= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\003\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l38;  goto l37;
  l38:;	  yypos= yypos38; yythunkpos= yythunkpos38;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l36;  yyDo(yy_1_int_value, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "int_value", yybuf+yypos));
  return 1;
  l36:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "int_value", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_rec_spec()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "rec_spec"));  if (!yy_col_spec()) goto l39;  if (!yy_s()) goto l39;  if (!yy_index()) goto l39;
  yyprintf((stderr, "  ok   %s @ %s\n", "rec_spec", yybuf+yypos));
  return 1;
  l39:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "rec_spec", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_col_spec()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 2, 0);
  yyprintf((stderr, "%s\n", "col_spec"));  if (!yy_name()) goto l40;  yyDo(yySet, -2, 0);  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l40;  if (!yymatchChar(':')) goto l40;  yyText(yybegin, yyend);  if (!(YY_END)) goto l40;  if (!yy_name()) goto l40;  yyDo(yySet, -1, 0);  yyDo(yy_1_col_spec, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "col_spec", yybuf+yypos));  yyDo(yyPop, 2, 0);
  return 1;
  l40:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "col_spec", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_row_spec()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "row_spec"));  if (!yy_name()) goto l41;  yyDo(yySet, -1, 0);  if (!yy_s()) goto l41;  if (!yy_index()) goto l41;  yyDo(yy_1_row_spec, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "row_spec", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l41:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "row_spec", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_name()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "name"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l42;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\040\000\000\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l42;
  l43:;	
  {  int yypos44= yypos, yythunkpos44= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\040\377\003\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l44;  goto l43;
  l44:;	  yypos= yypos44; yythunkpos= yythunkpos44;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l42;  yyDo(yy_1_name, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "name", yybuf+yypos));
  return 1;
  l42:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "name", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_layer_name()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "layer_name"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l45;  if (!yymatchString("lazytables")) goto l45;  yyText(yybegin, yyend);  if (!(YY_END)) goto l45;
  yyprintf((stderr, "  ok   %s @ %s\n", "layer_name", yybuf+yypos));
  return 1;
  l45:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "layer_name", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_s()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "s"));
  {  int yypos47= yypos, yythunkpos47= yythunkpos;  if (!yy_ws()) goto l48;
  l49:;	
  {  int yypos50= yypos, yythunkpos50= yythunkpos;  if (!yy_ws()) goto l50;  goto l49;
  l50:;	  yypos= yypos50; yythunkpos= yythunkpos50;
  }  goto l47;
  l48:;	  yypos= yypos47; yythunkpos= yythunkpos47;  if (!yy_EOF()) goto l46;
  }
  l47:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "s", yybuf+yypos));
  return 1;
  l46:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "s", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_stmt()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "stmt"));
  {  int yypos52= yypos, yythunkpos52= yythunkpos;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l53;  if (!yymatchString("print")) goto l53;  yyText(yybegin, yyend);  if (!(YY_END)) goto l53;  if (!yy_s()) goto l53;  if (!yy_name()) goto l53;  yyDo(yySet, -1, 0);  yyDo(yy_1_stmt, yybegin, yyend);  goto l52;
  l53:;	  yypos= yypos52; yythunkpos= yythunkpos52;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l54;  if (!yymatchString("has")) goto l54;  yyText(yybegin, yyend);  if (!(YY_END)) goto l54;  if (!yy_s()) goto l54;  if (!yy_row_spec()) goto l54;  yyDo(yy_2_stmt, yybegin, yyend);  goto l52;
  l54:;	  yypos= yypos52; yythunkpos= yythunkpos52;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l55;  if (!yymatchString("has")) goto l55;  yyText(yybegin, yyend);  if (!(YY_END)) goto l55;  if (!yy_s()) goto l55;  if (!yy_col_spec()) goto l55;  yyDo(yy_3_stmt, yybegin, yyend);  goto l52;
  l55:;	  yypos= yypos52; yythunkpos= yythunkpos52;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l56;  if (!yymatchString("has")) goto l56;  yyText(yybegin, yyend);  if (!(YY_END)) goto l56;  if (!yy_s()) goto l56;  if (!yy_rec_spec()) goto l56;  yyDo(yy_4_stmt, yybegin, yyend);  goto l52;
  l56:;	  yypos= yypos52; yythunkpos= yythunkpos52;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l57;  if (!yymatchString("get")) goto l57;  yyText(yybegin, yyend);  if (!(YY_END)) goto l57;  if (!yy_s()) goto l57;  if (!yy_rec_spec()) goto l57;  yyDo(yy_5_stmt, yybegin, yyend);  goto l52;
  l57:;	  yypos= yypos52; yythunkpos= yythunkpos52;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l58;  if (!yymatchString("set")) goto l58;  yyText(yybegin, yyend);  if (!(YY_END)) goto l58;  if (!yy_s()) goto l58;  if (!yy_rec_spec()) goto l58;  if (!yy_s()) goto l58;  if (!yy_int_value()) goto l58;  yyDo(yy_6_stmt, yybegin, yyend);  goto l52;
  l58:;	  yypos= yypos52; yythunkpos= yythunkpos52;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l59;  if (!yymatchString("set")) goto l59;  yyText(yybegin, yyend);  if (!(YY_END)) goto l59;  if (!yy_s()) goto l59;  if (!yy_rec_spec()) goto l59;  if (!yy_s()) goto l59;  if (!yy_str_value()) goto l59;  yyDo(yy_7_stmt, yybegin, yyend);  goto l52;
  l59:;	  yypos= yypos52; yythunkpos= yythunkpos52;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l60;  if (!yymatchString("delete")) goto l60;  yyText(yybegin, yyend);  if (!(YY_END)) goto l60;  if (!yy_s()) goto l60;  if (!yy_rec_spec()) goto l60;  yyDo(yy_8_stmt, yybegin, yyend);  goto l52;
  l60:;	  yypos= yypos52; yythunkpos= yythunkpos52;  if (!yy_var_stmt()) goto l51;
  }
  l52:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "stmt", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l51:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "stmt", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_meta_stmt()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "meta_stmt"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l61;  if (!yymatchString("describe")) goto l61;  yyText(yybegin, yyend);  if (!(YY_END)) goto l61;  if (!yy_s()) goto l61;  if (!yy_name()) goto l61;  yyDo(yySet, -1, 0);  yyDo(yy_1_meta_stmt, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "meta_stmt", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l61:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "meta_stmt", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_EOL()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "EOL"));
  {  int yypos63= yypos, yythunkpos63= yythunkpos;  if (!yy_nl()) goto l64;  goto l63;
  l64:;	  yypos= yypos63; yythunkpos= yythunkpos63;  if (!yy_EOF()) goto l62;
  }
  l63:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "EOL", yybuf+yypos));
  return 1;
  l62:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "EOL", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_ui_stmt()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "ui_stmt"));
  {  int yypos66= yypos, yythunkpos66= yythunkpos;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l67;  if (!yymatchString("help")) goto l67;  yyText(yybegin, yyend);  if (!(YY_END)) goto l67;  yyDo(yy_1_ui_stmt, yybegin, yyend);  goto l66;
  l67:;	  yypos= yypos66; yythunkpos= yythunkpos66;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l68;  if (!yymatchString("layer")) goto l68;  yyText(yybegin, yyend);  if (!(YY_END)) goto l68;  if (!yy_s()) goto l68;  if (!yy_layer_name()) goto l68;  yyDo(yy_2_ui_stmt, yybegin, yyend);  goto l66;
  l68:;	  yypos= yypos66; yythunkpos= yythunkpos66;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l65;  if (!yymatchString("quit")) goto l65;  yyText(yybegin, yyend);  if (!(YY_END)) goto l65;  yyDo(yy_3_ui_stmt, yybegin, yyend);
  }
  l66:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "ui_stmt", yybuf+yypos));
  return 1;
  l65:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "ui_stmt", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_top_stmt()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "top_stmt"));
  {  int yypos70= yypos, yythunkpos70= yythunkpos;  if (!yy_ui_stmt()) goto l71;  if (!yy_EOL()) goto l71;  goto l70;
  l71:;	  yypos= yypos70; yythunkpos= yythunkpos70;  if (!yy_meta_stmt()) goto l72;  if (!yy_EOL()) goto l72;  goto l70;
  l72:;	  yypos= yypos70; yythunkpos= yythunkpos70;  if (!yy_stmt()) goto l73;  if (!yy_EOL()) goto l73;  yyDo(yy_1_top_stmt, yybegin, yyend);  goto l70;
  l73:;	  yypos= yypos70; yythunkpos= yythunkpos70;
  l74:;	
  {  int yypos75= yypos, yythunkpos75= yythunkpos;
  {  int yypos76= yypos, yythunkpos76= yythunkpos;  if (!yy_EOL()) goto l76;  goto l75;
  l76:;	  yypos= yypos76; yythunkpos= yythunkpos76;
  }  if (!yymatchDot()) goto l75;  goto l74;
  l75:;	  yypos= yypos75; yythunkpos= yythunkpos75;
  }  if (!yy_EOL()) goto l69;  yyDo(yy_2_top_stmt, yybegin, yyend);
  }
  l70:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "top_stmt", yybuf+yypos));
  return 1;
  l69:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "top_stmt", yybuf+yypos));
  return 0;
}

#ifndef YY_PART

typedef int (*yyrule)();

YY_PARSE(int) YYPARSEFROM(yyrule yystart)
{
  int yyok;
  if (!yybuflen)
    {
      yybuflen= 1024;
      yybuf= malloc(yybuflen);
      yytextlen= 1024;
      yytext= malloc(yytextlen);
      yythunkslen= 32;
      yythunks= malloc(sizeof(yythunk) * yythunkslen);
      yyvalslen= 32;
      yyvals= malloc(sizeof(YYSTYPE) * yyvalslen);
      yybegin= yyend= yypos= yylimit= yythunkpos= 0;
    }
  yybegin= yyend= yypos;
  yythunkpos= 0;
  yyval= yyvals;
  yyok= yystart();
  if (yyok) yyDone();
  yyCommit();
  return yyok;
  (void)yyrefill;
  (void)yymatchDot;
  (void)yymatchChar;
  (void)yymatchString;
  (void)yymatchClass;
  (void)yyDo;
  (void)yyText;
  (void)yyDone;
  (void)yyCommit;
  (void)yyAccept;
  (void)yyPush;
  (void)yyPop;
  (void)yySet;
  (void)yytextmax;
}

YY_PARSE(int) YYPARSE(void)
{
  return YYPARSEFROM(yy_top_stmt);
}

#endif


    TVoid
ReplDo
    (
    Tnc8 *pUtterance
    )
    {
    ReplSetInput(pUtterance, FALSE);
    while(!g_parsingError && ReplGetCaretPosition() <= strlen(pUtterance))
        YYPARSE();
    }

  
