#include <stdio.h>
#include <string.h>

#include "repl.hpp"

   int 
main(int argc, char **argv) 
  {
  Initialize_repl();
  if (argc > 2)
    {
    puts("Too Many Arguments");
    ReplDoHelp();
    }
  else 
    {
    if(argc > 1)
      {
      printf("Reading \"%s\"...\n", argv[1]);
      FILE *filein = fopen(argv[1], "r");
      if(filein)
        {
        while(fgets(lineBuf, sizeof(lineBuf), filein))
          {
          printf("stdin > %s", lineBuf);
          if(lineBuf[strlen(lineBuf)-1] == '\n')
            lineBuf[strlen(lineBuf)-1] = '\r';
          ReplSetInput(lineBuf, FALSE);
          yyparse();
          }
        }
      }
    while(!ReplItsQuittingTime())
      {
      ReplDoPrompt(lineBuf, sizeof(lineBuf));
      g_parsingFinished = FALSE;
      g_parsingError = FALSE;
      yyparse();
      if(g_parsingError)
         {
         puts("Syntax Error");
         ReplDoHelp();
         }
      }
    }
  ReplDoQuit();
  return 0;
  }
