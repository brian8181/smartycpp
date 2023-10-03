/* Reverse Polish Notation calculator. */
%{
	#include <stdio.h>
	#include <math.h>
	int yylex (void);
	void yyerror (char const *);
%}

%token NUM
%token VAR
%token OPEN_PAREN
%token CLOSE_PAREN
%token ASTERIC
%token TEXT
%token FUNC

%% 

input:
	%empty
	| ";"
	| input line
	;
	
line: 
	'\n'
	| expr '\n' { printf ("%.10g\n", $1); }
	;

expr: 
	NUM
		| expr expr '+' { $$ = $1 + $2; }
	VAR 
		| expr expr '-'  { $$ = $1 + $2; }
	FUNC
		| function
		;

function:
		TEXT
		| expr expr "*" { $$ = $1 * $2 }
		;

%%

#include <ctype.h>
#include <stdlib.h>

int yylex (void)
{
	int c = getchar ();

	while (c == ’ ’ || c == ’\t’)
		c = getchar ();

	if (c == ’.’ || isdigit (c))
	{
		ungetc (c, stdin);
		if (scanf ("%lf", &yylval) != 1)
			abort ();
		return NUM;
	}
	else if (c == EOF)
	(
		return YYEOF;
	}
	else
	{
		return c;
	}
}

int main (void)
{
	return yyparse ();
}

#include <stdio.h>
/* Called by yyparse on error. */
void yyerror (char const *s)
{
	fprintf (stderr, "%s\n", s);
}	

