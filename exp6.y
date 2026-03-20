%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token NUMBER

%%
input:
    | input line
    ;

line:
      '\n'
    | expr '\n'   { printf("Result = %d\n", $1); }
    ;

expr:
      expr '+' term   { $$ = $1 + $3; }
    | expr '-' term   { $$ = $1 - $3; }
    | term            { $$ = $1; }
    ;

term:
      term '*' factor { $$ = $1 * $3; }
    | term '/' factor { $$ = $1 / $3; }
    | factor          { $$ = $1; }
    ;

factor:
      '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter expressions:\n");
    yyparse();
    return 0;
}
