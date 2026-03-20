%{
#include "y.tab.h"
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }

[ \t]       ;   // ignore spaces

\n          return '\n';

.           return yytext[0];
%%

int yywrap() {
    return 1;
}


bison -d calc.y
flex calc.l
gcc lex.yy.c calc.tab.c -o calc
./calc
