%{
#include <stdio.h>
%}

%%
[aeiouAEIOU]    { printf("%s", yytext); }
.|\n            ;   // ignore everything else
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
