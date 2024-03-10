/*
   File Name:  streamy.l
   Build Date: Wed Feb 14 12:02:37 AM CST 2024
   Version:    0.0.1
*/
%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "streamy.tab.h"

    // #include <stdio.h>
    // #include "y.tab.h"

    // void count();

    // struct bufstack
    // {
    //     struct bufstack *prev;
    //     YY_BUFFER_STATE bs;
    //     int lineno;
    //     char *filename;
    //     FILE *f;
    // } *curbs = 0;

    /* previous entry */
    /* saved buffer */
    /* saved line number */
    /* name of this file */
    /* current file */

    // char *curfilename;
    /* name of current input file */
    // int newfile(char *fn);
    // int popfile(void);


    // #define YYERROR(str) yyerror("%s\n", str);
    // extern char *yytext;
    // extern int yyleng;
    // extern int yylineno;
    // int yylex(void);
    // void yyerror(char *);
    // extern YYSTYPE yylval;
    int fileno(FILE *);

    //YYSTYPE yylval;
    // void* pyyval;
    // char* lex_text[256];
%}

OPEN_BRACE                  "{"
CLOSE_BRACE                 "}"
EQUALS_EQUALS               "=="
SYMBOL                       $[A-Za-z]+[A-Za-z0-9]*
TEXT                         [\\w\\s\\=$><^/#@~&*.%!~`_:\"'\\\\,]*
STRING_LITERAL               "\"[\\w\\s\\=$><^/#@~&*.%!~`_:\"'\\\\,]\""
NUMERIC_LITERAL              "[\\d]+.[\\d]*"

%%

{OPEN_BRACE}                {
                                // yyless(yyleng-1); /* return last quote */
                                // yymore();
                                return OPEN_BRACE;
                            }
{CLOSE_BRACE}               {
                                //printf("CLOSE_BRACE: %s\n", yytext );
                                // yyless(yyleng-1); /* return last quote */
                                // yymore();
                                return CLOSE_BRACE;
                            }
{EQUALS_EQUALS}             {
                                //printf("SYMBOL: %s\n", yytext );
                                return EQUALS_EQUALS;
                            }

{TEXT}                      {
                                //printf("TEXT: %s\n", yytext );
                                return TEXT;
                            }
{SYMBOL}                    {
                                //printf("SYMBOL: %s\n", yytext );
                                return SYMBOL;
                            }
{STRING_LITERAL}            {
                                //printf("SYMBOL: %s\n", yytext );
                                return STRING_LITERAL;
                            }
{NUMERIC_LITERAL}           {
                                return NUMERIC_LITERAL;
                            }

%%

int yywrap()
{
    return 1;
}

/* int main(int argc, char** argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "need filename\n");
        return 1;
    }

    if(newfile(argv[1]))
        yylex();
} */
